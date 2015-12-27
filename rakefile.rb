PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

load "scripts/helper.rb"

project_file = get_value_from_env('project', './project.yml')

Ceedling.load_project(config: project_file)

load_extra_scripts(project_file)

desc 'Build and deploy'
task :build_and_deploy do
  system "rake hw:flash"
end

task :default => %w[ build_and_deploy test:all ]
