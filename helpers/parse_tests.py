#!env python
import argparse
import collections
import json
import os
import re
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
      print(f"{suite} -- {test}")
  return tests
      
      
      
      
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
    
  print("key")
  test_dict = {"tests" : []}
  for key, tests in all_tests.items():
    for test in tests:
      test_dict["tests"].append({
        "suite" : key,
        "test_group" : test,
        "value" : 10,
        "tests" : [ test ]
      })
  print(json.dumps(test_dict, indent=2))
    
  

if __name__ == "__main__":
  main()