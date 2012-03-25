/**
 * Copyright © 2007 Kevin Twidle, Imperial College, London, England.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * Contact: Kevin Twidle <kpt@doc.ic.ac.uk>
 *
 * Created on Jun 4, 2007
 *
 * $Log:$
 */

package net.ponder2.support;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 * Check that rmiregistry is running, keep asking until it is running. This
 * program does a system.exit from wherever it likes. Once it spots the
 * rmiregistry working, it's bye bye
 * 
 * @author Kevin Twidle
 * @version $Id:$
 */
public class CheckRMI {

  String locations[] = { "rmiregistry", "/bin/rmiregistry", "\\bin\\rmiregistry.exe"};

  private Runtime runtime;

  CheckRMI() {
    runtime = Runtime.getRuntime();
    checkRmi();

    System.out.println("The RMI registry is not running, it will be started now.");
    System.out.println("If running under Windows you may have to hit ctrl-C after");
    System.out.println("it has been started and re-run the ant command.");
    startRegistry();
    for (int i = 0; i < 5; i++) {
      sleep(1);
      checkRmi();
    }
    while (true) {
      doDialog();
      checkRmi();
    }
  }

  void doDialog() {
    JFrame frame = null;
    Object[] options = { "Cancel", "Check Again"};
    int n = JOptionPane.showOptionDialog(frame,
        "Failed to start rmiregistry\nPlease start it and click Check Again\nIf you are running Safari on Windows\nplease stop it and run this program again!", "RMI Registry",
        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[1]);
    if (n != 1)
      System.exit(1);
  }

  void startRegistry() {
    String home = System.getenv("JAVA_HOME");
    for (int i = 0; i < locations.length; i++) {
      startRegistryAt(locations[i]);
      startRegistryAt(home + locations[i]);
    }
  }

  void startRegistryAt(String name) {
    try {
      System.out.println("Trying to start rmi registry: " + name);
      runtime.exec(name);
      sleep(1);
      checkRmi();
    }
    catch (IOException e) {
    }
  }

  private void checkRmi() {
    boolean answer = false;
    try {
      Naming.lookup("//localhost/BSN");
      answer = true;
    }
    catch (MalformedURLException e) {
      e.printStackTrace();
      System.err.println("Something wrong in CheckRMI, please report it");
      System.exit(1);
    }
    catch (RemoteException e) {
      answer = false;
    }
    catch (NotBoundException e) {
      answer = true;
    }
    System.out.println("rmiregistry" + (answer ? "" : " not") + " running");
    if (answer)
      System.exit(0);
  }

  private void sleep(int secs) {
    try {
      Thread.sleep(secs * 1000);
    }
    catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }

  }

  /**
   * @param args
   */
  public static void main(String[] args) {
    new CheckRMI();
  }

}
