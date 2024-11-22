const std = @import("std");

const prime = @cImport({
    @cInclude("prime.c");
});

const c_hashtable = @cImport({
    @cInclude("hash_table.c");
});

test "is_prime" {
    var is = prime.is_prime(7);
    try std.testing.expect(is == prime.IS_PRIME);

    is = prime.is_prime(8);
    try std.testing.expect(is == prime.NOT_PRIME);

    is = prime.is_prime(1);
    try std.testing.expect(is == prime.UNKNOWN);
}

test "next_prime" {
    const next = prime.next_prime(9);
    try std.testing.expect(next == 12);
}

test "ht_new and ht_destroy" {
    const ht = c_hashtable.ht_new();
    c_hashtable.ht_destroy(ht);
}

test "ht_insert" {
    const ht = c_hashtable.ht_new();
    defer c_hashtable.ht_destroy(ht);

    c_hashtable.ht_insert(ht, "foo", "bar");
    const value = std.mem.span(c_hashtable.ht_search(ht, "foo"));

    try std.testing.expectEqualStrings(value, "bar");
}

test "ht_search" {
    const ht = c_hashtable.ht_new();
    defer c_hashtable.ht_destroy(ht);

    c_hashtable.ht_insert(ht, "foo", "bar");

    const value = std.mem.span(c_hashtable.ht_search(ht, "foo"));
    try std.testing.expectEqualStrings(value, "bar");

    const undefinedValue = c_hashtable.ht_search(ht, "baaz");
    try std.testing.expect(undefinedValue == null);
}

test "ht_has" {
    const ht = c_hashtable.ht_new();
    defer c_hashtable.ht_destroy(ht);

    c_hashtable.ht_insert(ht, "foo", "bar");
    try std.testing.expect(c_hashtable.ht_has(ht, "foo"));
    try std.testing.expect(!c_hashtable.ht_has(ht, "baaz"));
}

test "ht_delete" {
    const ht = c_hashtable.ht_new();
    defer c_hashtable.ht_destroy(ht);

    c_hashtable.ht_insert(ht, "foo", "bar");
    c_hashtable.ht_delete(ht, "foo");
    try std.testing.expect(!c_hashtable.ht_has(ht, "foo"));
}
