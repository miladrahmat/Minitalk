# Minitalk
<p align="center">
<img src="https://github.com/miladrahmat/42-badges/blob/master/badges/minitalkm.png"><img width=144 src="https://github.com/user-attachments/assets/65bdd92b-d5ab-4adb-b86c-fde82061d1ab">
</p>
<p align="center">
<b>Communication program for data exchange using UNIX signals</b>

## Content

- [Introduction](#introduction)

## Introduction

This project is a data exchange program using UNIX signals to communicate between client and server.

The client sends a string bit by bit to to the server using user defined signals `SIGUSR1` and `SIGUSR2`. Once the server receives the entire message it displays the string.
