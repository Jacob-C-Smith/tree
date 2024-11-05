Testing binary tree:
 - Basic testing practices (make sure functions conform to their descriptions, null pointer tests, valgrind, etc)
 - For change scenarios, serialize the result and compare against the expected result
 - Test different shapes (fully unbalanced, fully balanced, half and half, different depths)
 - Test operations on nodes with < no child | left child | right child | both child >
 
 ╭───────────┬───────────╮  ╭───────────┬───────────╮
 │           │           │  │           │           │
 │         ╭─┴─╮         │  │         ╭─┴─╮         │
 │         │ N │         │  │         │ N │         │
 │         ╰─┬─╯         │  │         ╰─┬─╯         │
 │           │           │  │           │           │
 │     ╭─────┴─────╮     │  │     ╭─────┴─────╮     │
 │    ─┴─         ─┴─    │  │   ╭─┴─╮       ╭─┴─╮   │
 │                       │  │   │ A │       │ B │   │
 │                       │  │   ╰─┬─╯       ╰─┬─╯   │
 │                       │  │     │           │     │
 ╰───────────────────────╯  ╰─────┴───────────┴─────╯

 ╭───────────┬───────────╮  ╭───────────┬───────────╮
 │           │           │  │           │           │
 │         ╭─┴─╮         │  │         ╭─┴─╮         │
 │         │ N │         │  │         │ N │         │
 │         ╰─┬─╯         │  │         ╰─┬─╯         │
 │           │           │  │           │           │
 │     ╭─────┴─────╮     │  │     ╭─────┴─────╮     │
 │   ╭─┴─╮        ─┴─    │  │    ─┴─        ╭─┴─╮   │
 │   │ A │               │  │               │ B │   │
 │   ╰─┬─╯               │  │               ╰─┬─╯   │
 │     │                 │  │                 │     │
 ╰─────┴─────────────────╯  ╰─────────────────┴─────╯
