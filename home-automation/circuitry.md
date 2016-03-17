<!--
Title: Circuitry Basics
Summary: This document was used to promote the event on the blog.
Author: G. L. Clark, II
Date Created: February 16, 11:15
Date Modified:{{ file.mtime }}
Filename: circuitry-basics.md
-->

# Circuitry Basics

Learning the basics of electronics isn't that difficult. This should be a quick overview into practical electronics. It is not my goal to delve deeply into the science of electrical engineering. If you want to know more about the science of basic electronics, [Wikipedia](https://en.wikipedia.org/wiki/Electronics) is a good place to start your search.

## Electricity

There are two types of electrical signals, alternating current (AC), and direct current (DC).

With alternating current, the direction electricity flows throughout the circuit is constantly reversing. You may even say that it is alternating direction. The rate of reversal is measured in Hertz, which is the number of reversals per second. When they say that the US power supply is 60 Hz, what they mean is that it is reversing 120 times per second (twice per cycle).

With Direct Current, electricity flows in one direction between power and ground. In this arrangement there is always a positive source of voltage and ground (0V) source of voltage. You can test this by reading a battery with a multimeter. For great instructions on how to do this, check out [Ladyada's multimeter](http://www.ladyada.net/learn/multimeter) page. You will want to measure [voltage](http://www.ladyada.net/learn/multimeter/voltage.html) in particular.

Electricity is typically defined as having a voltage and a current rating. Voltage is rated in Volts and current is rated in Amps. For instance, a brand new 9V battery would have a voltage of "9" and a current of around 500mA (500 milliamps).

To get a better understanding of these different measurements, check out this video on Ohm's Law. It will show you what the measurements mean and how they relate to each other.

## Circuits

A circuit is a complete and closed path through which electric current can flow. In other words, a closed circuit would allow the flow of electricity between power and ground. An open circuit would break the flow of electricity between power and ground.

Anything that is part of a closed system and allows electricity to flow between power and ground is considered to be part of the circuit.

## Resistance

The next very important consideration to keep in mind is that electricity in a circuit must be used. There should be something wired between the positive and ground that adds resistance to the flow of electricity. If positive voltage is connected directly to ground and does not first pass through something that adds resistance, like a motor, then a short circuit will result. A short occurs when the positive voltage is connected directly to ground.

If electricity passes through a component (or group of components) that does not add enough resistance to the circuit, a short will occur ([see Ohm's Law video](http://www.youtube.com/watch?v=_-jX3dezzMg)).

Shorts are bad because they will result in your battery and/or circuit overheating, breaking, catching on fire, and/or exploding.

**_It is very important to prevent short circuits by making sure that the positive voltage is never wired directly to ground._**

Always keep in mind that electricity always follows the path of least resistance to ground.This means is that if you give positive voltage the choice to pass through a motor or follow a wire straight to ground, it will follow the wire because the wire provides the least resistance. This also means that by using the wire to bypass the source of resistance straight to ground, you have created a short circuit. Always make sure that you never accidentally connect positive voltage to ground while wiring things in parallel.

Also note that a switch does not add any resistance to a circuit and simply adding a switch between power and ground will create a short circuit.

---

#### References

- [Basic Electronics](http://www.instructables.com/id/Basic-Electronics/?ALLSTEPS) by Randy Sarafan
