# Minitalk
<p align="center">
<img src="https://github.com/miladrahmat/42-badges/blob/master/badges/minitalkm.png"><img width=144 src="https://github.com/user-attachments/assets/65bdd92b-d5ab-4adb-b86c-fde82061d1ab">
</p>
<p align="center">
<b>Communication program for data exchange using UNIX signals</b>

## Content

- [Introduction](#introduction)
- [Examples](#examples)
- [Bonus](#bonus)
- [Installation](#installation)

## Introduction

This project is a data exchange program using UNIX signals to communicate between client and server.

The client sends a string bit by bit to to the server using user defined signals `SIGUSR1` and `SIGUSR2`. Once the server receives the entire message it displays the string.

## Examples

The Makefile produces two programs `client` and `server`.

When the `server` program is run, it outputs its PID:
```
./server
Server PID: 131743
```
The servers PID is the first argument to `client`, the second argument is the message:
```
./client 131743 "Hello World"
```
After the `client` program is run, the `server` outputs the message given to `client` as an argument:
```
./server
Server PID: 131743
Hello World
```

## Bonus

The bonus part of the project requires that the `server` acknowledges every message received by sending back a signal to the
client and support for unicode characters.

When a message is sent the `client` then awaits for the acknowledgement signal from the server, when the signal is received it outputs `Message sent successfully!` and exits the program.

The message can also include unicode characters since every character is sent bit by bit to the `server` the characters are outputted correctly.

For example:
```
./client 131743 "Hello World 😊"
Sending message..
Message sent successfully!
```
```
./server
Server PID: 131743
Hello World 😊
```

## Installation

To install and test the program, run the following on the command line:
```
git clone https://github.com/miladrahmat/Minitalk.git
cd Minitalk
make
```
