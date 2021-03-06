#*****************************************************************************
#
# Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
# Produced at the Lawrence Livermore National Laboratory
# LLNL-CODE-442911
# All rights reserved.
#
# This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
# full copyright notice is contained in the file COPYRIGHT located at the root
# of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
#
# Redistribution  and  use  in  source  and  binary  forms,  with  or  without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of  source code must  retain the above  copyright notice,
#    this list of conditions and the disclaimer below.
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
#    documentation and/or other materials provided with the distribution.
#  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
#    be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
# ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
# LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
# DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
# SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
# CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
# LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
# OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.
#*****************************************************************************
"""
 file: setup_tests.py
 author: Cyrus Harrison <cyrush@llnl.gov>
 created: 10/14/2010
 description:
    Provides 'ExecuteTests' a distutils command class that automatically
    collects and launches unittest test cases from scripts in the 'tests'
    subdir.

    I created this simple one file module b/c nose & setuptools are not always
    available/installable on all of the systems I develop python modules on.

    To use this class in a distutils setup project:
     A) Create test scripts in the subdir 'tests'
     B) In your setup.py:
        #import the test module
        import setup_tests
        # Add the custom command to the 'cmdclass' dictonary in your setup call:
        setup( ...
              cmdclass = { 'test': setup_tests.ExecuteTests})

     C) Invoke 'python setup.py test' to run tests

"""

import os
import glob
import sys

from distutils.core import Command
from unittest import TextTestRunner, TestLoader, TestSuite, TestCase
 
class ExecuteTests(Command):
    description = "locate and execute scripts containing unit tests."
    user_options = [  ('verbose', None, "Verbose output"),
                      ('tests-dir=', None, "Directory containg tests"),
                      ('filter=',None,"Filter used to select which tests to execute")]
    boolean_options = ['verbose']
    negative_opt = {'quiet' : 'verbose'}
    def initialize_options(self):
        self.verbose   = 1
        self.tests_dir = "tests"
        self.filter    = None
    def finalize_options(self):
        self.tests_dir = os.path.join(os.getcwd(),self.tests_dir)
    def run(self):
        """
        Finds and executes unit tests in the 'tests' subdir.
        Because TestLoader imports the tests as a module this method
        automatically creates/updates the 'tests/__init__.py' to
        import all python scripts in the 'tests' subdir.
        """
        self.run_command('build')
        sys.path.insert(0,os.path.join(os.getcwd(),"build","lib"))
        self.tests  = []
        # make sure the 'tests' subdir actually exists.
        if not os.path.isdir(self.tests_dir):
            print "ExecuteTests: <Error> 'tests' subdir not found!"
        else:
            self.find_tests()
            self.gen_tests_init()
            # create a test suite.
            tests = TestLoader().loadTestsFromNames([t[0] for t in self.tests])
            if not self.filter is None:
                tests = self.filter_tests(tests)
            # run the test suite if it actually contains test cases.
            run_verbosity = 2
            if self.verbose == 0:
                run_verbosity = 0
            if tests.countTestCases() > 0:
                runner = TextTestRunner(verbosity=run_verbosity)
                runner.run(tests)
            else:
                print "ExecuteTests: <Warning> No test cases found!"
        sys.path.pop(0)
    def find_tests(self):
        """
        Helper called by 'run' to find python scripts in the 'tests' subdir.
        """
        for f in glob.glob(os.path.join(self.tests_dir,"*.py")):
            if not f.endswith('__init__.py'):
                test = os.path.splitext(os.path.basename(f))[0]
                test = '.'.join(['tests',test])
                self.tests.append( (test,f))
        if len(self.tests) > 0 and self.verbose:
            print "Detected Test Scripts:"
            for t in self.tests:
                print " %s @ %s)" % (t[0],t[1])
    def filter_tests(self,tests):
        """
        Filters detected tests according to pattern passed to 
        the "--filter=" argument.
        """
        return self.__filter_test_suite(tests,self.filter)
    def __filter_test_suite(self,ts,filter):
        """
        Recursively filters tests from a test suite object according
        to the passed filter. 
        """
        res = TestSuite()
        for t in ts:
            if isinstance(t,TestSuite):
                res.addTest(self.__filter_test_suite(t,filter))
            elif issubclass(type(t),TestCase):
                if t.id().count(filter) !=0:
                    res.addTest(t)
        return res
    def gen_tests_init(self):
        """
        Helper called by 'run' to update the 'tests/__init__.py' file.

        Note: If no python scripts exist in the 'tests' subdir
              'tests/__init__.py' will be removed.
        """
        tests_init = os.path.join(self.tests_dir,"__init__.py")
        if len(self.tests) > 0:
            f = open(tests_init,"w")
            f.write("# module header auto generated by "
                    "setup_tests.ExecuteTests\n")
            # import each test script as part of the 'tests' module.
            for t in self.tests:
                f.write("import %s\n" % t[0])
        elif os.path.exists(tests_init):
            # remove the module init file if no test scripts are found.
            os.remove(tests_init)