## <font color="#F2853F" style="font-size:24pt">newt complete </font>

Performs bash autocompletion using tab. It is not intended to be called directly from the command line.

#### Install bash autocompletion

```no-highlight
    $ brew install bash-completion
    Updating Homebrew...
    <snip>
    Bash completion has been installed to:
      /usr/local/etc/bash_completion.d
    ==> Summary
    🍺  /usr/local/Cellar/bash-completion/1.3_1: 189 files, 607.8K
```

#### Enable autocompletion for newt

```no-highlight
    $ complete -C "newt complete" newt
```

#### Usage

Hit tab and see possible completion options or completed command.

```no-highlight
    $ newt target s
    set   show  
    $ newt target show
```
