#file: builder_plugins/installed/efd_notifier.rb
class EfdNotifier
  def initialize(project = nil)
        CruiseControl::Log.event("EFD Ready", :info)
  end

  def build_finished(build)
        if build.failed?
                efd("off 2")
                efd("cycle_on 3")
        else
                efd("cycle_off 3")
                efd("on 2")
        end
  end

  def build_fixed(build, previous_build)
    efd("cycle_off 3")
    efd("on 2")
  end

  private

  def efd(cmd)
        command = "/home/projects/efd/efd1 #{cmd}"
        CruiseControl::Log.event("EFD: #{command}", :info)
        system(command)
  end

end

Project.plugin :efd_notifier
