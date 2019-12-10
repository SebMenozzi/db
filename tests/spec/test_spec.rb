describe 'database' do
    def run_script(commands)
        raw_output = nil
        IO.popen("../db", "r+") do |pipe|
            commands.each do |command|
                pipe.puts command
            end

            pipe.close_write

            # Read entire output
            raw_output = pipe.gets(nil)
        end
        raw_output&.split("\n")
    end

    it 'insert / retreive a row' do
        result = run_script([
            "insert 1 user1 person1@example.com",
            "select",
            "exit",
        ])

        expect(result).to match_array([
            "(1, user1, person1@example.com)",
        ])
    end

    it 'print an error message when table is full' do
        script = (0..1300).map do |i|
            "insert #{i} user#{i} person#{i}@example.com"
        end
        script << "exit"

        result = run_script(script)

        expect(result).to match_array([
          "Error: Table full.",
        ])
    end

    it 'insert / retreive a row #2' do
        username = "a"*32
        email = "b"*255

        result = run_script([
            "insert 1 #{username} #{email}",
            "select",
            "exit",
        ])

        expect(result).to match_array([
            "(1, #{username}, #{email})"
        ])
    end

    it 'insert a too long username' do
        username = "a"*33
        email = "b"*255

        result = run_script([
            "insert 1 #{username} #{email}",
            "exit",
        ])

        expect(result).to match_array([
            "String is too long."
        ])
    end

    it 'insert a too long email' do
        username = "a"*32
        email = "b"*256

        result = run_script([
            "insert 1 #{username} #{email}",
            "exit",
        ])

        expect(result).to match_array([
            "String is too long."
        ])
    end

    it 'insert a too long email twice' do
        username = "a"*32
        email = "b"*256

        result = run_script([
            "insert 1 #{username} #{email}",
            "insert 2 #{username} #{email}",
            "exit",
        ])

        expect(result).to match_array([
            "String is too long.",
            "String is too long.",
        ])
    end

    it 'insert with an negative id' do
        result = run_script([
            "insert -1 test test@gmail.com",
            "exit",
        ])

        expect(result).to match_array([
            "ID must be positive.",
        ])
    end

end
