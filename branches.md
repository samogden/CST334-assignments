# How to develop

There are two kinds of development we care about in this project:
There are two branches for development of code changes in this class
1. Year-to-year updates:
  - Base branch: `staging`
  - Core warning: ***This code can be directly pushed into `base` and should never contain golden code
  - These are updates such as changing to use a continuous time scheduler more exhaustive unit tests
  - These will be deployed at the end of each semester, or at least prior to the official assignment of each assignment
2. Development of new projects or new code:
  - Base branch: `dev`
  - Core: ***This code will contain golden code.  Pulling code from it should be sanitized prior to merging into `base`
  - PageDirectory MMUs, and persistence 
  