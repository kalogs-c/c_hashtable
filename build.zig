const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.host;
    const optimize = b.standardOptimizeOption(.{});

    const unit_tests = b.addTest(.{
        .root_source_file = b.path("src/tests.zig"),
        .target = target,
        .optimize = optimize,
    });

    unit_tests.linkLibC();
    unit_tests.addIncludePath(b.path("src"));

    const run_tests = b.addRunArtifact(unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_tests.step);

    const lib = b.addStaticLibrary(.{
        .name = "c_hashtable",
        .target = target,
        .optimize = optimize,
    });

    const files = [_][]const u8{
        "src/hash_table.c",
        "src/prime.c",
    };

    const flags = [_][]const u8{
        "-std=c23",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-O3",
    };

    lib.addCSourceFiles(.{
        .files = &files,
        .flags = &flags,
    });

    lib.linkLibC();
    b.installArtifact(lib);
}
