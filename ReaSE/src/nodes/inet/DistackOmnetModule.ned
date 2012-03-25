package rease.nodes.inet;

//
// Basic simple module for implementation of the attack detection
// system Distack (by Mayer|Gamer)
//
simple DistackOmnetModule
{
    parameters:
       string configId;
    gates:
      input  in;
      input sigIn[];
      output out;
      output sigOutIP;
      output sigOutTCP;
      output sigOutUDP;
      output sigOutRAO;
}
