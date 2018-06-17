# Contributing

This is a brief guide on how to contribute to the project.

## Getting Started

1. First let's clone a repo development branch:   
   `git clone https://login:pass@gitlab.com/ptyshevs/cw.git --recursive -b dev`
2. Run make:   
   `make`

That's all. You can expect `dev` branch to be up-to-date and in moderately WIP
mode.   
This means, all binaries are executable and can provide the functionality
described in milestones,   
no unexpected behavior is allowed (apart from stubs for
future releases).

## Making Changes

1. Create a branch for each feature you want to develop: 
   `git checkout -b feature_name`

2. Commit you work to the corresponding remote branch
   `git push origin feature_name`

## Writing Code

1. Respect the Norm.
2. Every function must have a docstring - short description of the arguments,
   expected behavior and caveats.
You are writing this not for others, but for
   your later self debugging piles of code angrily.
3. Use descriptive names for files. Try to make each file modular.
4. Any function not exposed by file should be `static`.

## Submitting Changes

When you consider the feature finished, you have two options.
1. The first one is to merge changes by yourself locally and push the
   merge commit to the repo:   
  1.1 `git checkout dev`   
  1.2 `git merge feature_name`   
You are the one responsible for resolving any conflict emerged. Try to be reasonable so not to disrupt,   
or even worse, damage the work of other contributors. The short guide is below.

2. The other one is to create a merge request   
  2.1 Push the button here:   
    <img src="docs/screenshots/merge-request.png" width="400px" />   
  2.2 Select source branch `feature_name` and target branch `dev`,
Describe the changes made, choose assignee person to be responsible for the merge.   
    <img src="docs/screenshots/merge-form.png" width="400px" />   

## Resolving Conflicts

1. Open Corewar in CLion   
2. Go to VCS-Git-Resolve Conflicts...   
<img src="docs/screenshots/vcs-git-resolve.png" width="400px" />   
3. You see a list of files with conflicts:   
<img src="docs/screenshots/conflict_files.png" width="200px" />   
4. For each file, open it and choose the appropriate piece of conflicting code.   
<img src="docs/screenshots/resolve.png" width="400px" />   
5. Once finished, commit the merge and push to the repo.
