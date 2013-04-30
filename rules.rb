require 'fileutils'

def count_semicolons file
  File.read(file).count(";")  
end

def count_many_semicolons files
  files.reduce(0) { |memo, file| memo + count_semicolons(file) }
end

starting_directory = Dir.pwd
changed_semicolons = count_many_semicolons(Dir["**/*.cpp"])

tmp_path = "../_tmp_git_dir"
Dir.mkdir(tmp_path)
Dir.chdir(tmp_path) do
  `git clone "#{starting_directory}" .`
  original_semicolons = count_many_semicolons(Dir["**/*.cpp"])
  diff = changed_semicolons - original_semicolons
  if diff.abs <= 25
    puts "OK!"
  else
    puts "BAD!"
  end
  puts "New Semicolons: #{changed_semicolons}"
  puts "Old Semicolons: #{original_semicolons}"
  puts "Diff: %+d" % [diff]
end

FileUtils.rm_rf tmp_path
gets
