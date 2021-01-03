# skeleton

Project to save structure for future projects which creates targets:
- main executable target (`skeleton`)
- main static library target (`dataapi`) which contains functionality of the project
- tests executable target (`dataapitests`) - tests written using gtest library, tests `dataapi`
- common target (`common`) which is also a static library containing common helpful functionality shared between all other targets

Also this project creates dev targets:
- `dataapi_sanitized` - sanitized version of library, used to linking with `dataapitests_sanitized`
- `common_sanitized` - sanitized version of library, used to linking with `dataapitests_sanitized`
- `dataapitests_sanitized` - sanitized version of test cases, used to check `UB` in code
- `coverage` - runs test cases and checks code coverage (also creates `html` file with information about covered and non covered code regions)
- `test` - runs test cases
- `package` - creates `rpm` package
