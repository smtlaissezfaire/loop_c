require "spec_helper"

describe "escheme" do
  def run(cmd)
    cmd = cmd.dup.gsub('"', '\"')

    if ENV['VALGRIND'] == "true"
      FileUtils.mkdir_p "spec/logs"
      out = `valgrind --log-file=spec/logs/valgrind.log bin/escheme -e "#{cmd}"`

      File.read("spec/logs/valgrind.log").should =~ /ERROR SUMMARY: 0/
      out
    else
      `bin/escheme -e "#{cmd}"`
    end
  end

  describe "numbers" do
    it "should output an int as an int" do
      pending do
        run("1").should == "1"
      end
    end

    it "should output a different int as the correct int" do
      pending do
        run("2").should == "2"
      end
    end

    it "should parse space from a number" do
      pending do
        run("   2 ").should == "2"
      end
    end

    it "should parse a floating point number" do
      pending do
        run("3.32").should == "3.320000"
      end
    end

    it "should parse a different floating point number" do
      pending do
        run("270.999").should == "270.998993"
      end
    end
  end

  describe "strings" do
    it "should output a string as a string" do
      pending do
        run('"foo"').should == '"foo"'
      end
    end

    it "should output the correct string" do
      pending do
        run('"foobar"').should == '"foobar"'
      end
    end
  end

  describe "booleans - #t and #f" do
    it "should have #t as true" do
      pending do
        run("#t").should == "#t"
      end
    end

    it "should have #f as false" do
      pending do
        run("#f").should == "#f"
      end
    end
  end

  describe "multiple objects" do
    it "should print two on two lines" do |variable|
      pending do
        run("1 2").should == "1\n2"
      end
    end
  end

  describe "lists" do
    describe "quoting" do
      describe "with (quote)" do
        it "should output a sym for a sym" do
          pending do
            run("(quote foo)").should == "foo"
          end
        end

        it "should output a list for a list" do
          pending do
            run("(quote ())").should == "()"
          end
        end

        it "should output the contents of a quoted list" do
          pending do
            run("(quote (foo bar baz))").should == "(foo bar baz)"
          end
        end
      end
    end

    describe "car" do
      it "should be able to car a list" do
        pending do
          run("(car (quote (a b c)))").should == "a"
        end
      end

      it "should be able to car a list" do
        pending do
          run("(car (quote (x y z)))").should == "x"
        end
      end

      it "should raise an error on an empty list" do
        pending do
          run("(car (quote ()))").should == "ERROR!  Can't car an empty list"
        end
      end
    end

    describe "cdr" do
      it "should return the rest of the list" do
        pending do
          run("(cdr (quote (a b c)))").should == "(b c)"
        end
      end
    end
  end
end