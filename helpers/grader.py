#!env python

import argparse
import collections
import json
import logging
import os
import subprocess
from argparse import Namespace
from pprint import pprint
from typing import List
from collections import defaultdict

import re

logging.basicConfig()
log = logging.getLogger()
log.setLevel(logging.DEBUG)

class ScoringItem(object):
  pass

class ScoringGroup(ScoringItem):
  def __init__(self, name, value):
    self.name = name
    self.value = value
    self.tests = []

class ScoringTest(ScoringItem):
  def __init__(self, suite, test_group, value, test_name=None):
    self.suite = suite
    self.test_group = test_group
    self.value = value
    self.test_name = test_name if test_name is not None else test_group

class Test(object):
  def __init__(self, name, num_assertions, status):
    self.name = name
    self.num_assertions = num_assertions
    self.status = status
    self.value = 0
  def __str__(self):
    return f"{self.name}:{self.status}"
  def set_value(self, value):
    self.value = value
  
  def get_score(self):
    return self.value if self.status == "PASSED" else 0.0
  
  @classmethod
  def create_from_dict(cls, json_dict):
    return cls(
      json_dict["name"],
      json_dict["assertions"],
      json_dict["status"]
    )

class Suite(object):
  def __init__(self, name, passed, failed, errored, skipped, tests=[]):
    self.name = name
    self.passed = passed
    self.failed = failed
    self.errored = errored
    self.skipped = skipped
    self.tests = dict()
    for test in tests:
      self.tests[test.name] = test
  def add_test(self, test):
    self.tests[test.name] = test
  
  def get_score(self):
    results = { "PASSED" : [], "FAILED" : [] }
    score = 0.0
    for t in self.tests.values():
      score += t.get_score()
      if t.status == "PASSED":
        results["PASSED"].append(t.name)
      else:
        results["FAILED"].append(t.name)
    return score, results
  
  def __str__(self):
    return f"{self.name} : ({self.passed}/{len(self.tests)}"
  @classmethod
  def create_from_dict(cls, json_dict):
    new_suite = cls(
      json_dict["name"],
      json_dict["passed"],
      json_dict["failed"],
      json_dict["errored"],
      json_dict["skipped"]
    )
    for test_dict in json_dict["tests"]:
      new_suite.add_test(Test.create_from_dict(test_dict))
    return new_suite
  

class Results(object):
  def __init__(self, passed, failed, errored, skipped, suites=[]):
    self.passed = passed
    self.failed = failed
    self.errored = errored
    self.skipped = skipped
    self.suites = dict()
    for suite in suites:
      self.suites[suite.name] = suite
  def add_suite(self, suite):
    self.suites[suite.name] = suite
  def __str__(self):
    return f"Results: {self.passed} / {sum([len(suite.tests.keys()) for (name, suite) in self.suites.items()])}"
  
  def get_score(self):
    results = {}
    score = 0.0
    for s in self.suites.values():
      suite_score, suite_results = s.get_score()
      score += suite_score
      results[s.name] = suite_results
    return score, results
    #return sum([s.get_score() for s in self.suites.values()])
  
  def score(self, scoring_tests: List[ScoringTest]):
    for score in scoring_tests:
      self.suites[score.suite].tests[score.test_name].set_value(score.value)
      
  @classmethod
  def create_from_dict(cls, json_dict):
    new_result = cls(
      json_dict["passed"],
      json_dict["failed"],
      json_dict["errored"],
      json_dict["skipped"]
    )
    for suite_dict in json_dict["test_suites"]:
      new_result.add_suite(Suite.create_from_dict(suite_dict))
    return new_result


def parse_flags() -> Namespace:
  parser = argparse.ArgumentParser()
  parser.add_argument("--assignment_dir", default=os.getcwd(), help="Path to assignment directory")
  parser.add_argument("--output", default="/tmp/results.json")
  args: Namespace = parser.parse_args()
  return args

def run_unittests(path_to_assignment_directory):
  os.chdir(path_to_assignment_directory)
  proc = subprocess.Popen(["./unit_tests", "-j1", "--json", "--timeout", "60"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  proc.wait()
  stdout = proc.stdout.read().decode('latin-1')
  stderr = proc.stderr.read().decode('latin-1')
  
  return parse_unit_tests_json(stdout)

def parse_unit_tests_json(in_lines) -> Results:
  json_lines = fix_json(in_lines)
  json_dict = json.loads(json_lines)
  
  results = Results.create_from_dict(json_dict)
  return results

def fix_json(json_str):
  in_lines = json_str.split('\n')
  out_lines = []
  curr_line_i = 0
  while curr_line_i < len(in_lines):
    if "messages" in in_lines[curr_line_i]:
      out_lines[-1] = out_lines[-1][:-1]
      # Then we suspect we'll be starting to messages field
      # for right now we'll just skip it -- going forward we may actually fix it
      #while in_lines[curr_line_i].strip() != ']':
      while not in_lines[curr_line_i].strip().endswith(']'):
        curr_line_i += 1
      else:
        curr_line_i += 1
        
    out_lines.append(in_lines[curr_line_i])
    curr_line_i += 1
  return '\n'.join(out_lines)

def get_scoring_tests(tests):
  scoring_tests = []
  for test_group in tests:
    if "tests" in test_group.keys():
      for test in test_group["tests"]:
        scoring_tests.append(
          ScoringTest(
            test_group["suite"],
            test_group["test_group"],
            test_group["value"] / len(test_group["tests"]),
            test
          )
        )
    else:
      scoring_tests.append(
        ScoringTest(
          test_group["suite"],
          test_group["test_group"],
          test_group["value"]
        )
      )
  return scoring_tests


def parse_scoring(path_to_scoring) -> List[ScoringItem]:
  try:
    with open(path_to_scoring) as fid:
      json_dict = json.load(fid)
    scoring_tests = []
    if "groups" in json_dict.keys():
      groups = []
      for group in json_dict["groups"]:
        scoring_group = ScoringGroup(group["name"], group["value"])
        scoring_group.tests = get_scoring_tests(json_dict["tests"])
        groups.append(group)
      return groups
    if "tests" in json_dict.keys():
      return get_scoring_tests(json_dict["tests"])
  except FileNotFoundError:
    return []


def make_test(path_to_assignment_directory):
  os.chdir(path_to_assignment_directory)
  proc = subprocess.Popen(["make", "unit_tests"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  proc.wait()
  
  stdout = proc.stdout.read().decode()
  stderr = proc.stderr.read().decode()
  
  if proc.returncode == 0:
    return True, stderr
  else:
    return False, stderr

def find_function(source_code, target_function_name):
  
  def skip_multiline_comment(lines, line_i):
    while "*/" not in lines[line_i]:
      line_i += 1
    return line_i
  
  def capture_function(lines, line_i):
    start_i = line_i
    line_i += 1
    depth = 1
    while depth > 0 and line_i < len(lines):
      cleaned_line = ' '.join(lines[line_i].split('//')[0]) # Not super strong, but whatever
      if '/*' in cleaned_line:
        line_i = skip_multiline_comment(lines, line_i)
        continue
      depth += cleaned_line.count('{') - cleaned_line.count('}')
      log.debug(f"depth: {depth}")
      line_i += 1
    return lines[start_i:line_i]
  
  with open(source_code, 'r') as fid:
    source_lines = [l.rstrip() for l in fid.readlines()]
    
  function_pattern = re.compile("^\s*\w*\s*\**\s*(\w+)\(.*\).*{.*$")
  function_lines = []
  
  curr_line_i = 0
  while curr_line_i < len(source_lines):
    curr_line = source_lines[curr_line_i]
    result =  function_pattern.search(curr_line)
    if result is not None:
      function_name = result.group(1)
      log.debug(f"function_name: {function_name} (\"{curr_line}\")")
      if function_name == target_function_name:
        function_lines = capture_function(source_lines, curr_line_i)
        break
    curr_line_i += 1
  
  log.debug('\n'.join(function_lines))



def main():
  args = parse_flags()
  scoring_tests = parse_scoring(os.path.join(os.path.abspath(args.assignment_dir), "scoring.json"))
  results_json = {}
  build_success, build_log = make_test(os.path.abspath(args.assignment_dir))
  if build_success:
    test = run_unittests(os.path.abspath(args.assignment_dir))
    test.score(scoring_tests)
    score, results = test.get_score()
    results_json["score"] = score
    results_json["suites"] = results
  else:
    results_json = {
      "build_status" : "FAILURE",
      "score" : 0.0
    }
    log.error("Build failed")
  
  if len(scoring_tests) == 0:
    results_json["score"] = "Not calculated"
    
  results_json["build_logs"] = json.encoder.JSONEncoder().encode(build_log),
  print(json.dumps(results_json, indent=4))
  with open(args.output, 'w') as fid:
    json.dump(results_json, fid, indent=4)
  

if __name__ == "__main__":
  main()