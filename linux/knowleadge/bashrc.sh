# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples


# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth
HISTSIZE=1000
HISTFILESIZE=2000
export HISTTIMEFORMAT="%d/%m/%y %T "

shopt -s histappend
shopt -s checkwinsize

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi
# ------------------------------------------------------------------
# GIT PROMPT - banch and status 
# ------------------------------------------------------------------
_git_branch() {
  # nazwa gałęzi albo tag przy HEAD; puste poza repo
  local b
  b=$(git symbolic-ref --short -q HEAD 2>/dev/null) \
    || b=$(git describe --tags --exact-match 2>/dev/null) \
    || return 0
  # status skrótami: ✗ (modified), + (staged), ? (untracked), ↑/↓ ahead/behind
  local st=""
  git diff --no-ext-diff --quiet --ignore-submodules || st+="✗"
  git diff --no-ext-diff --cached --quiet --ignore-submodules || st+="+"
  [ -n "$(git ls-files --others --exclude-standard)" ] && st+="?"
  local ab; ab=$(git rev-list --left-right --count @{upstream}...HEAD 2>/dev/null)
  if [ -n "$ab" ]; then
    local behind=${ab%%	*}; local ahead=${ab##*	}
    [ "$ahead" -gt 0 ] && st+="↑$ahead"
    [ "$behind" -gt 0 ] && st+="↓$behind"
  fi
  [ -n "$st" ] && st=" $st"
  printf '(%s%s)' "$b" "$st"
}

# ------------------------------------------------------------------
# SET A FANCY PROMPT (non-color, unless we know we "want" color)
# ------------------------------------------------------------------
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w \[\033[36m\]$(_git_branch)\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w $(_git_branch)\$'
fi

unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'

fi

if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
#---------------------------------------------------
################## ALIAS SECTION ##################
#---------------------------------------------------
alias ll='ls -lh'
alias la='ls -lah'
alias vi='vim'
alias rt='/home/ute/test_repository/resources/DevKr/FTK12/rt.sh'
alias rtt='/home/ute/test_repository/resources/DevKr/run_test_and_backup_results.sh'
alias rd='/home/ute/test_repository/resources/DevKr/FTK12/rd.sh'
alias rl='tail -f /home/ute/results/latest/robot_debug.log'
alias admin='firefox --new-tab 192.168.255.129 &'
alias tltype='/home/ute/test_repository/resources/DevKr/testline_get_type.py | cut -f3'
alias cus_update='sudo /opt/cus/bin/cus-update'
# --------------------------------------
alias ..="cd .."
alias ...="cd ../.."
alias ....="cd ../../.."
alias start_xterm='xterm -geometry 88x51+1000+10 -fa "Monospace" -fs 10 -bg black -fg yellow -T "Terminal 1" -e /bin/bash & xterm -geometry 93x28+30+10 -fa "Monospace" -fs 10 -bg black -fg yellow -T "Terminal 2" -e /bin/bash & xterm -geometry 93x19+30+640 -fa "Monospace" -fs 10 -bg black -fg yellow -T "Terminal 3" -e /bin/bash &'
export LS_OPTIONS='--color=auto'
eval "`dircolors`"
alias ls='ls $LS_OPTIONS'
alias l='ls $LS_OPTIONS -lA'
alias grep='grep --color=auto'
alias ip='ip -c'

# -------------- pjetruszka aliases --------------
export LESS=-Xr
export TERM=xterm-256color
PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
alias cdlogs='cd /home/cus/logs/; cd $(ls -td -- */ | head -n 1); cd $(ls -td -- */ | head -n 1);'
alias res_vnc="xrandr --newmode '1904x990_60.00'  155.75  1904 2016 2216 2528  990 993 1003 1027 -hsync +vsync; xrandr --addmode Virtual-1 '1904x990_60.00'; xrandr --output Virtual-1 --mode '1904x990_60.00';"
alias rtt='/home/ute/test_repository/resources/DevKr/run_test_and_backup_results.sh'
alias tt='telnet 0 20000'
alias enb_check='/home/ute/test_repository/resources/DevKr/enb_check_build.sh'
alias epcsim_start='/home/ute/test_repository/resources/DevKr/epcsim_start.sh'
# --------------------------------------

# --------------------------------------
alias gitsetup='
  git config --global user.email "grzegorz.1.golonka@nokia.com" && \
  git config --global user.name "Grzegorz Golonka" && \
  git config --global core.editor "vim"
  git config --global credential.helper store
'
# --------------------------------------
alias clone_gears='git clone https://wrgitlab.ext.net.nokia.com/RAN/gears/krakow.iht.git'
alias clone_cicus='git clone https://wrgitlab.ext.net.nokia.com/tsex/cicus.git'
alias clone_iht='git clone "https://ggolonka@gerrit.ext.net.nokia.com/gerrit/a/MN/LTE/IHT/iht-e2e-ci" && (cd "iht-e2e-ci" && gitdir=$(git rev-parse --git-dir); curl -o ${gitdir}/hooks/commit-msg https://gerrit.ext.net.nokia.com/gerrit/static/commit-msg ; chmod +x ${gitdir}/hooks/commit-msg)'
alias vmip="ip -4 addr show eth0"
alias linkSuites='ln -s /home/ute/MN/UTE/robotlte/testsuite/IHT/suites/ /home/ute/RobotSuites'
alias reload='source ~/.bashrc'
alias editrc='vim ~/.bashrc && reload'

# --------------------------------------
alias uex_cmd="UEX_CONFIG_PATH=/opt/cus/etc/uex/uex.exs iex -S mix" 
alias run_uex="UEX_CONFIG_PATH=/opt/cus/etc/uex/uex.exs mix run -e 'UEx.CT.run_test(suite: $1, group: $2)'"
alias go_scripts="cd /home/ute/MN/UTE/krakow.iht/cus/testsuite/SCRIPTS"

export PYENV_ROOT="$HOME/.pyenv"
export PATH="$PYENV_ROOT/bin:$PATH"

# -----------------PROXY SETUP---------------------
export https_proxy='http://proxy-lab.krk-lab.nsn-rdnet.net:8080'
export http_proxy='http://proxy-lab.krk-lab.nsn-rdnet.net:8080'
# --------------------------------------

# --------------------------------------
function vscode_setup() {
  local code_extension_list=(
    elixir-lsp.elixir-ls
    robocorp.robotframework-lsp
    JakeBecker.elixir-ls
    ms-python.python
    ms-python.vscode-pylance
    ms-python.debugpy
    ms-python.pylint
    formulahendry.code-runner
  )
  cd /home/ute/Downloads/ || return

  wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg

  sudo install -o root -g root -m 644 packages.microsoft.gpg /usr/share/keyrings/
  rm packages.microsoft.gpg

  echo "deb [arch=amd64 signed-by=/usr/share/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" | \
  sudo tee /etc/apt/sources.list.d/vscode.list > /dev/null

  mkdir -p ~/.vscode-server/bin
  wget -qO- https://update.code.visualstudio.com/latest/server-linux-x64/stable | tar -xz -C ~/.vscode-server/bin/

  sudo apt update
  sudo apt install -y 

  for extension_id in "${code_extension_list[@]}"; do
    code --install-extension  "$extension_id"
  done
}

# --------------------------------------
function prio() {
  sudo renice -n -20 -p "$1"
}

# --------------------------------------
function set_prios(){
  PROCESS=$1
  ps aux | grep "$1" | awk ' NR==2 { print $2 }' | xargs -n1 -I{} sudo renice -n -20 -p {} 
}

# --------------------------------------
function ping_ctrl(){
  ctrl_nr=$1
  if [[ "$arg" =~ ^ctrl-([0-9]+)$ ]]; then
    num="${BASH_REMATCH[1]}"
  else
    echo "Wrong given argument. Using default ctrl-1"
    num=1
  fi
  ip="192.168.200.$num"
  echo "Ping ctrl$num. Stop by CTRL+C"
  ping "$ip"
}

# --------------------------------------
function ping_enb(){
  ping "192.168.255.129"
}

# --------------------------------------
function update_rc() {
    vim ~/.bashrc && reload && echo "Bashrc changed successfully. Nice !!."
}

# --------------------------------------
function show_rc(){
  cat ~/.bashrc 
}

# --------------------------------------
function go() {
  HOME_PATH="/home/ute"
  UTE_PATH="/home/ute/MN/UTE"
    case "$1" in
        robot) path="$UTE_PATH/robotlte" ;;
        gears) path="$UTE_PATH/gears/gears.krakow.iht" ;;
        cicus) path="$HOME_PATH/cicus" ;;
        gerrit) path="$HOME_PATH/iht-e2e-ci" ;;
        *)
            echo "USE: go_repo [nazwa_repo]"
            echo "Available: robot, gears, cicus, gerrit"
            return 1
            ;;
    esac
    cd "$path" || return
    echo ">> PWD now: $path"
    ls -la
}

# --------------------------------------
# PING CTRL AND WAIT UNTIL ITS AVAILABLE
# THEN CHECK WHETHER CUSMMESSAGES.LOG IS AVAIALABLE 
# --------------------------------------
function ctrl_messages() {
  HOST="192.168.200.1"
  LOG_FILE="/tmp/CusMessages.log"
  PASS="oZPS0POrRieRtu"
  USER="toor4nsn"
  echo "Wait for $HOST to respond..."

  until ping -c1 -W1 "$HOST" &>/dev/null; do
    sleep 2
  done 

  echo "Host is eachable. Connectying via SSH"
  sshpass -p "$PASS"  ssh -o StrictHostKeyChecking=no  "$USER@$HOST" <<EOF
    if [ -f "$LOG_FILE" ]; then
        echo "File $LOG_FILE exists. Tailing..."
        tail -f "$LOG_FILE"
    else
        echo "File $LOG_FILE does not exist yet."
    fi
EOF
}

# --------------------------------------
function get_testline_pdu() {
  GITLAB_TOKEN="ZeXZpQiQmNE9M4x3wZ_6"
  USER="ggolonka"
  TARGET_REPO_PATH="/home/ute/MN/UTE/krakow.iht"
  POSSIBLE_SECOND_REPO_PATH="/home/ute/MN/UTE/gears/krakow.iht"
  repo_path=""
  if [ -d "$TARGET_REPO_PATH" ]; then
    repo_path=$TARGET_REPO_PATH
  elif [ -d "$POSSIBLE_SECOND_REPO_PATH" ]; then
    repo_path=$POSSIBLE_SECOND_REPO_PATH
  else
    repo_path="$TARGET_REPO_PATH"
    echo "Repo not found in paths. Let's clone it"
    git clone https://${USER}:${GITLAB_TOKEN}@wrgitlab.ext.net.nokia.com/RAN/gears/krakow.iht.git   $TARGET_REPO_PATH
  fi
  echo "Repo path: ${repo_path}"

  echo "Settuping python environment"
  export PYENV_ROOT="$HOME/.pyenv"
  export PATH="$PYENV_ROOT/bin:$PATH"
  eval "$(pyenv init -)"
  eval "$(pyenv virtualenv-init -)"
  pyenv activate test_repo
  echo "Running script"
  local pdu_ip_addr=$(python "${repo_path}/cus/testsuite/SCRIPTS/config/get_tl_config_param.py" "_pdu1" "addr")
  google-chrome --new-tab "https://$pdu_ip_addr" &
}

# --------------------------------------
function run_sxap_config(){
   GEARS_DIR=/home/ute/MN/UTE/krakow.iht/cus/testsuite
   bash $GEARS_DIR/SCRIPTS/uex/configure_sxap.sh ENBs=10.0.1.2,10.0.1.22 MMEs=10.0.1.1
}
# --------------------------------------
