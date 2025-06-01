# DirVis 🌳

**Directory Visualiser** - A fast, lightweight command-line tool for visualizing directory structures with tree output.

## Usage

```bash
dirvis [DIRECTORY] [OPTIONS]
```

#### Arguments
- `DIRECTORY` - Path to the directory to visualise

#### Options
- `--show-hidden` - Include hidden files and directories in output
- `--max-depth <N>` - Limit directory traversal to N levels deep
- `--no-colour` - Use default colours (white) when printing ***not implemented yet***
- `--help` - Display help information

## Examples

### Basic Usage
Visualise the ```foo``` directory:
```bash
dirvis foo
```
```
foo/
├── world.c
├── hello.c
└── bar/
    ├── buzz/
    └── fizz/
        └── fizzbuzz.c
```

### Show Hidden Files
Include hidden files and directories in the output:
```bash
dirvis foo --show-hidden
```
```
foo/
├── world.c
├── .env/
│   ├── secrets
│   └── .super.secrets
├── hello.c
├── .config
└── bar/
    ├── buzz/
    └── fizz/
        └── fizzbuzz.c
```

### Limit Depth
Control how deep the tool traverses subdirectories:
```bash
dirvis foo --show-hidden --max-depth 2
```
```
foo/
├── world.c
├── .env/
│   ├── secrets
│   └── .super.secrets
├── hello.c
├── .config
└── bar/
    ├── buzz/
    └── fizz/
```
## Roadmap
- Specify directories to exclude from recursion
- Config file to change primary/accent colours





