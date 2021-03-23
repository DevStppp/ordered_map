# ordered_map

## Clang-Format
: Version 10 기준으로 작성 [Clang 10 Style Option](https://releases.llvm.org/10.0.0/tools/clang/docs/ClangFormatStyleOptions.html)

* [JSON for Modern C++](https://github.com/nlohmann/json)의 .clang-formant을 기초로 해서 Clang10에 맞게 수정 및 필요한 부분만 이용

* Visual Studio Code - Settings.json
```
{
    "C_Cpp.clang_format_path": "/usr/bin/clang-format",
    "C_Cpp.clang_format_style": "file",
}
```