pushd %~dp0
    build\Release\caller test1 > test1.log
    build\Release\caller test2 > test2.log
popd