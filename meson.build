
project(
  'blocktimer',
  'c',
  version: '1.0.0',
  default_options: [
    'warning_level=3',
    'c_std=gnu11'
  ]
)

if get_option('buildtype') == 'debug'
  add_project_arguments('-DDEBUGBUILD', language: 'c')
endif

subdir('src')

sysconfdir = get_option('sysconfdir')
bindir = get_option('bindir')
prefix = get_option('prefix')

if bindir.startswith('/')
  blocktimer_bin = bindir / 'blocktimer'
else
  blocktimer_bin = prefix / bindir / 'blocktimer'
endif

svc_conf = configuration_data()
svc_conf.set('BLOCKTIMER_BIN', blocktimer_bin)

if get_option('conf')
  install_data(
    'block.conf',
    install_dir: sysconfdir / 'blocktimer',
    install_mode: 'rw-r--r--'
  )
endif


if get_option('openrc')
  openrc_script = configure_file(
    input: 'open-rc/blocktimer.in',
    output: 'blocktimer-openrc',
    configuration: svc_conf
  )

  install_data(
    openrc_script,
    install_dir: sysconfdir / 'init.d',
    rename: 'blocktimer',
    install_mode: 'rwxr-xr-x'
  )
endif

if get_option('systemd')
  systemd_dep = dependency('systemd', required: false)

  if systemd_dep.found()
    systemd_system_unit_dir = systemd_dep.get_variable(
      pkgconfig: 'systemdsystemunitdir',
      default_value: '/usr/lib/systemd/system'
    )

    install_data(
      configure_file(
        input: 'systemd/blocktimer.service.in',
        output: 'blocktimer.service',
        configuration: svc_conf
      ),
      install_dir: systemd_system_unit_dir
    )
  endif
endif
