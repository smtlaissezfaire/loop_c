require "spec_helper"

describe "loop" do
  def run(cmd)
    cmd = cmd.dup.gsub('"', '\"')

    if ENV['VALGRIND'] == "true"
      FileUtils.mkdir_p "spec/logs"
      out = `valgrind --suppressions=./boehm-gc.suppressions --log-file=spec/logs/valgrind.log bin/loop -e "#{cmd}"`

      log = File.read("spec/logs/valgrind.log")
      log.should =~ /ERROR SUMMARY: 0/
      log.should =~ /definitely lost: 0 bytes in 0 blocks/
      out
    else
      `bin/loop -e "#{cmd}"`
    end
  end

  def run_with_printing(cmd)
    run "(print #{cmd})"
  end

  describe "numbers" do
    it "should output an int as an int" do
      run_with_printing("1").should == "1"
    end

    it "should output a different int as the correct int" do
      run_with_printing("2").should == "2"
    end

    it "should parse space from a number" do
      run_with_printing("   2 ").should == "2"
    end

    it "should parse a floating point number" do
      run_with_printing("3.32").should == "3.320000"
    end

    it "should parse a different floating point number" do
      run_with_printing("270.999").should == "270.998993"
    end
  end

  describe "strings" do
    it "should output a string as a string" do
      run_with_printing('"foo"').should == '"foo"'
    end

    it "should output the correct string" do
      run_with_printing('"foobar"').should == '"foobar"'
    end

    it "should allow for an empty string" do
      run_with_printing('""').should == '""'
    end

    it "should allow periods in strings" do
      run_with_printing('"."').should == '"."'
    end

    it "should allow a capital letter in a string" do
      run_with_printing('"A"').should == '"A"'
    end

    it "should allow caps in strings" do
      pending do
        run_with_printing('"ABCDEFGHIJKLMNOPQRSTUVWXYZ"').should == '"ABCDEFGHIJKLMNOPQRSTUVWXYZ"'
      end
    end
  end

  describe "booleans - #t and #f" do
    it "should have #t as true" do
      run_with_printing("#t").should == "#t"
    end

    it "should have #f as false" do
      run_with_printing("#f").should == "#f"
    end
  end

  describe "multiple objects" do
    it "should print two on two lines" do |variable|
      run("(print 1) (print 2)").should == "12"
    end
  end

  describe "lists" do
    describe "list function" do
      # it "should make a nil list" do
      #   run_with_printing("(list)").should == "()"
      # end
      #
      # it "should make a list" do
      #   run_with_printing("(list 1)").should == "(1)"
      # end
      #
      # it "should make a list with two elements" do
      #   pending do
      #     run_with_printing("(list 1 2)").should == "(1 2)"
      #   end
      # end
    end

    describe "quoting" do
      describe "with (quote)" do
        it "should output a sym for a sym" do
          run_with_printing("(quote foo)").should == "foo"
        end

        it "should output a list for a list" do
          run_with_printing("(quote ())").should == "()"
        end

        it "should output the contents of a quoted list" do
          run_with_printing("(quote (foo bar baz))").should == "(foo bar baz)"
        end

        it "should output the correct contents of multiple items" do
          run_with_printing("(quote (foo bar))").should == "(foo bar)"
        end

        it "should not be buggy..." do
          run_with_printing("(quote ((foo bar) (((()))) bar))").should == "((foo bar) (((()))) bar)"
        end

        # it "should throw an exception if more than one element is given to the quote" do
        #   run_with_printing("(quote foo bar)")
        # end
      end
    end

    describe "car" do
      it "should be able to car a list" do
        run_with_printing("(car (quote (a b c)))").should == "a"
      end

      it "should be able to car a different list" do
        run_with_printing("(car (quote (x y z)))").should == "x"
      end

      it "should raise an error on an empty list" do
        run_with_printing("(car (quote ()))").should == "FATAL ERROR: car: expects argument of type <pair>; given ()"
      end
    end

    describe "cdr" do
      it "should be the empty list when given one list element" do
        run_with_printing("(cdr (quote (a)))").should == "()"
      end

      it "should return the rest of the list, excluding the first item" do
        run_with_printing("(cdr (quote (a b c)))").should == "(b c)"
      end

      it "should raise an error on an empty list" do
        run_with_printing("(cdr (quote ()))").should == "FATAL ERROR: cdr: expects argument of type <pair>; given ()"
      end
    end

    describe "cons" do
      it "should be able to add an element to an empty list" do
        run_with_printing("(cons (quote a)
                   (quote ()))").should == "(a)"
      end

      it "should be able to add an element to a list with one element" do
        run_with_printing("(cons (quote a)
                   (quote (b)))").should == "(a b)"
      end

      it "should be able to cons a list onto another list" do
        run_with_printing("(cons (quote (a b))
                   (quote (a)))").should == "((a b) a)"
      end

      it "should be able to make a pair" do
        run_with_printing("(cons 1 2)").should == "(1 . 2)"
      end

      it "should make two sets of pairs" do
        run_with_printing("(cons 1 (cons 2 3))").should == "(1 2 . 3)"
      end
    end

    describe "defining functions + calling them" do
      it "should be able to print a function" do
        run_with_printing("(lambda () 10)").should == "#<proc>"
      end

      it "should be able to create a function and call it" do
        run_with_printing("((lambda () 10))").should == "10"
      end

      it "should return the correct value" do
        run_with_printing("((lambda () 20))").should == "20"
      end

      it "should be able to pass a value + return it" do
        run_with_printing("((lambda (x) x) 20)").should == "20"
      end

      it "should evaluate its arguments" do
        run_with_printing("((lambda (x) x)
                            (cons 1 2))").should == '(1 . 2)'
      end

      it "should evaluate lambda arguments" do
        run_with_printing("(((lambda (x) x)
                            (lambda () 10)))").should == "10"
      end
    end

    describe "equality with equal?" do
      it "should be true with true == true" do
        run_with_printing("(equal? #t #t)").should == "#t"
      end

      it "should be true with false equal? false" do
        run_with_printing("(equal? #f #f)").should == "#t"
      end

      it "should be false between different boolean types" do
        run_with_printing("(equal? #f #t)").should == "#f"
      end

      it "should be false with different numbers" do
        run_with_printing("(equal? 1 2)").should == "#f"
      end

      it "should be true between two symbols with the same name" do
        run_with_printing("(equal? (quote foo) (quote foo))").should == "#t"
      end

      it "should be false between different symbols" do
        run_with_printing("(equal? (quote foo) (quote bar))").should == "#f"
      end
    end

    describe "define" do
      it "should set a value in the environment" do
        run("(define x 10)
             (print x)").should == "10"
      end

      it "should return the value set in the environment" do
        run_with_printing("(define x 10)").should == "10"
      end

      it "should evaluate its argument (it should be able to chain defines)" do
        run("(define x 10)
             (define y x)
             (print y)").should == "10"
      end

      it "should store copies as copies, not as references" do
        code = <<-CODE
          (define x 10)
          (define y x)

          (define x 20)
          (print y)
        CODE

        run(code).should == "10"
      end

      it "should be able to define and run a function" do
        code = <<-CODE
          (define foo
            (lambda ()
              (quote ())))

          (print (foo))
        CODE

        run(code).should == "()"
      end

      it "should be able to define and run a function with one argument" do
        code = <<-CODE
          (define foo
            (lambda (x)
              x))

          (print (foo 10))
        CODE

        run(code).should == "10"
      end

      it "should be able to define and run a function with two arguments" do
        code = <<-CODE
          (define foo
            (lambda (x y)
              y))

          (print (foo 10 20))
        CODE

        run(code).should == "20"
      end

      it "should be able to pass a function to a function, and the function passed should be callable" do
        code = <<-CODE
          (define describe
            (lambda (fun)
              (fun)))

          (describe
            (lambda () (print 10)))
        CODE

        run(code).should == "10"
      end

      it "should allow dashes in identifiers" do
        run("(define foo-bar 10) (print foo-bar)").should == "10"
      end

      it "should allow underscores in identifiers" do
        run("(define foo_bar 10) (print foo_bar)").should == "10"
      end
    end

    describe "scoping variables" do
      it "should keep scope local" do
        code = <<-CODE
          (define x 10)

          ((lambda (x) x) 20)

          (print x)
        CODE

        run(code).should == "10"
      end

      it "should prefer argument values to environment values inside a function" do
        code = <<-CODE
          (define x 10)

          (define print-x
            (lambda (x)
              (print x)))

          (print-x 20)
        CODE

        run(code).should == "20"
      end
    end

    describe "cond" do
      it "should evaluate to the first true branch" do
        code = <<-CODE
          (cond (#t #t) (#f #f))
        CODE

        run_with_printing(code).should == "#t"
      end

      it "should return the first value in the true branch" do
        run_with_printing("(cond (#t 10) (#f #f))").should == "10"
      end

      it "should return the value in the first true branch (when the first true one is the second one)" do
        run_with_printing("(cond (#f 10) (#t 20))").should == "20"
      end

      it "should return false if given no arguments" do
        run_with_printing("(cond)").should == "#f"
      end

      it "should run the last clause if the last clause is an else" do
        run_with_printing("(cond (#f 1) (else 2))").should == "2"
      end
    end
  end
end