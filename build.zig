const std = @import("std");

const base_files = [_][]const u8{
    "src/hash_table.c",
    "src/prime.c",
};

const base_flags = [_][]const u8{
    "-std=c23",
    "-Wall",
    "-Wextra",
    "-Werror",
    "-O3",
};

fn build_lib(b: *std.Build) void {
    const ht = b.addStaticLibrary(.{
        .name = "libc_hashtable",
        .target = b.host,
        .optimize = b.standardOptimizeOption(.{}),
    });

    const files = base_files;
    const flags = base_flags;

    ht.addCSourceFiles(.{
        .files = &files,
        .flags = &flags,
    });

    ht.linkLibC();
    b.installArtifact(ht);
}

fn build_exe(b: *std.Build) void {
    const exe = b.addExecutable(.{
        .name = "c_hashtable",
        .target = b.host,
        .optimize = b.standardOptimizeOption(.{}),
    });

    const files = base_files ++ [_][]const u8{
        "src/main.c",
    };

    const flags = base_flags ++ [_][]const u8{
        "-g",
    };

    exe.addCSourceFiles(.{
        .files = &files,
        .flags = &flags,
    });

    exe.linkLibC();
    b.installArtifact(exe);
}

pub fn build(b: *std.Build) void {
    // build_lib(b);
    build_exe(b);
}
