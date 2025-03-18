## mystd

Study realization of all popular types from STL
- All types uses `mystd::` extension
- For everything with compilation/execution/testing, I use `cmake`
- At current moment, this code can't be used as library (skill issue)
- For testing all types, I use `ctest`
- Everything written in VS Code (some additional info)

In every realization, I add comments, which explains confused parts

What types already recreated
- `string` - `char` only, no `SSO`, no templates, no multithread support
