# Scheduler Project
## Overview
This project implements a robust operation scheduler in C, enabling serial execution of tasks at predetermined intervals.
It offers functionalities for adding, removing, and managing tasks efficiently. 
The scheduler is designed with high cohesion and loose coupling principles, ensuring each component's responsibility is well-defined and standalone.

## Features
Create: Initialize a new scheduler instance.

Destroy: Release resources and destroy the scheduler.

Add: Add a new task to the scheduler with a specified operation function and interval.

Remove: Remove a task from the scheduler using its unique identifier (UID).

Run: Start executing tasks in the scheduler.

Stop: Pause task execution.

Size: Get the number of tasks currently in the scheduler.

Is Empty: Check if the scheduler is empty.

Clear: Remove all tasks from the scheduler.

## Usage

Clone the repository.

Compile the source files.

Link the scheduler library with your project.

Include scheduler.h in your source files.

Utilize the provided API functions to interact with the scheduler.
