#!  /usr/bin/env python
# encoding: utf-8


APPNAME = "expected"
VERSION = "1.0.0"


def configure(conf):
    conf.set_cxx_std(11)


def build(bld):
    # Path to the expected repo
    expected_path = bld.dependency_node("expected-source")

    # Create system include for expected
    expected_include = expected_path.find_dir("include")

    bld(
        name="expected",
        export_includes=expected_include.abspath(),
    )

    if bld.is_toplevel():
        bld.program(
            features="cxx test",
            source=["example/main.cpp"],
            target="expected_tests",
            use=["expected"],
        )
