#!env python
import argparse
import collections
import json
import os
import re
import sys
from pprint import pprint

test_regex = re.compile(
  r"Test\(([a-zA-Z_\-0-9]*), ([a-zA-Z0-9_\-]*)(, disabled=)?.*$"
)


def parse_flags():
  parser = argparse.ArgumentParser()
  
  parser.add_argument(
    "--input_directory",
    default="/Users/ssogden/repos/classes/CST334-assignments/programming-assignments/PA2/tests"
  )
  parser.add_argument(
    "--output_file",
    default="scoring.json"
  )
  parser.add_argument(
    "--combine_by_suite",
    action="store_true",
    default=False  # Disable this later on
  )
  
  return parser.parse_args()

def parse_file(f):
  tests = collections.defaultdict(list)
  with open(f) as fid:
    lines = [l.strip() for l in fid.readlines()]
  for line in lines:
    result = test_regex.match(line)
    if result:
      suite = result.group(1)
      test = result.group(2)
      tests[suite].append(test)
  return tests
      

def combine_by_suite(all_tests):
  tests_by_suite = []
  for suite, tests in all_tests.items():
    tests_by_suite.append({
      "suite" : suite,
      "test_group" : suite,
      "value" : 10,
      "tests" : tests
    })
  return tests_by_suite
      
def main():
  args = parse_flags()
  
  all_tests = collections.defaultdict(list)
  for f in [
    os.path.join(args.input_directory, f)
    for f in os.listdir(args.input_directory)
    if f.endswith(".c")
  ]:
    for key, tests in parse_file(f).items():
      all_tests[key].extend(tests)


  if args.combine_by_suite:
    test_dict = {"tests" : combine_by_suite(all_tests)}
  else:
    test_dict = {"tests" : []}
    for key, tests in all_tests.items():
      for test in tests:
        test_dict["tests"].append({
          "suite" : key,
          "test_group" : test,
          "value" : 10,
          "tests" : [ test ]
        })
  #print(json.dumps(test_dict, indent=2))
  with open(args.output_file, 'w') as fid:
    print_tests(test_dict, fid=fid)

def print_tests(test_dict, indent=2, fid=sys.stdout):
  def print_indent(indent_level):
    print(' ' * indent * indent_level, end='', file=fid)

  def print_list(lst, indent_level):
    indent_level += 1
    print('[', file=fid)
    for i, itm in enumerate(lst):
      if i:
        print(", ", file=fid)
      print_indent(indent_level)
      if isinstance(itm, dict):
        print_dict(itm, indent_level)
      else:
        print(f"\"{itm}\"", end="", file=fid)
    print("", file=fid)
    indent_level -= 1
    print_indent(indent_level)
    print(']', file=fid)

  def print_dict(dct, indent_level):
    indent_level += 1
    print('{', end='', file=fid)
    for key, itm in dct.items():
      if key == "value":
        print(f"\"{key}\" : {itm},", end=' ', file=fid)
      elif key != "tests":
        print(f"\"{key}\" : \"{itm}\",", end=' ', file=fid)
    print("\"tests\" : ", file=fid)
    print_indent(indent_level)
    print_list(dct["tests"], indent_level)
    indent_level -= 1
    print_indent(indent_level)
    print('}', end="", file=fid)

  indent_level = 1

  print("{", file=fid)
  print_indent(indent_level)
  print(f"\"tests\" : ", end='', file=fid)
  print_list(test_dict["tests"], indent_level)
  print("}", file=fid)
    
  

if __name__ == "__main__":
  main()