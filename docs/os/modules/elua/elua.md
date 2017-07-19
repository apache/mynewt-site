# elua


### Description

This package contains a Lua interpreter. See http://lua.org for documentation of the language.

You can execute lua scripts either from console with shell or start the execution programmatically.

### Data structures

### Notes

Currently we don't have language extension modules which would go together with this one, but those should be added.

### List of Functions

| Function | Description |
|---------|-------------|
| [lua_init](lua_init.md) | Registers 'lua' command with shell. |
| [lua_main](lua_main.md) | Executes lua script in current task's context. Arguments given are passed to lua interpreter. |

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>
