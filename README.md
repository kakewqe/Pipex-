# 📄 Pipex

## 🇬🇧 English

The goal of this project is to reproduce the behavior of shell pipes using process creation and file descriptor management.

### Description

Pipex recreates the functionality of the Unix pipe (`|`) command.

This project helps you better understand:

- processes
- pipes
- file descriptors
- system calls

### Program

```bash
./pipex infile cmd1 cmd2 outfile
```

### How it works

- Opens input and output files
- Creates a pipe
- Executes commands using:
  - fork()
  - pipe()
  - dup2()
  - execve()
- Redirects standard input and output

### Compilation

```bash
make
```

### Example

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Equivalent to:

```bash
< infile grep hello | wc -l > outfile
```

### Skills Developed

- C programming
- Unix processes
- pipes
- file descriptors
- system programming
- process synchronization

---

## 🇫🇷 Français

Le but de ce projet est de reproduire le comportement des pipes Unix en utilisant la création de processus et la gestion des descripteurs de fichiers.

### Description

Pipex recrée le fonctionnement de l'opérateur de pipe (`|`) du shell Unix.

Ce projet permet de mieux comprendre :

- les processus
- les pipes
- les file descriptors
- les appels système

### Fonctionnement

- Ouvre les fichiers d'entrée et de sortie
- Crée un pipe
- Exécute les commandes avec :
  - fork()
  - pipe()
  - dup2()
  - execve()
- Redirige les flux standard

### Compilation

```bash
make
```

### Compétences travaillées

- langage C
- processus Unix
- pipes
- gestion des fichiers
- programmation système
- synchronisation de processus
