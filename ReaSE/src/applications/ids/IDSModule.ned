package rease.applications.ids;

simple IDSModule
{
    parameters:
      double dropRatio;
      int treshold;
    gates:
      input  in;
      output distack;
      output out;
      output toRateLimiter;
}
