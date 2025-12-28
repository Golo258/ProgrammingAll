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
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

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
alias admin='firefox --new-tab 192.168.255.129 &'
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
# --------------------------------------

# --------------------------------------
alias gitsetup='
  git config --global user.email "grzegorz.1.golonka@nokia.com" && \
  git config --global user.name "Grzegorz Golonka" && \
  git config --global core.editor "vim"
  git config --global credential.helper store
'
# --------------------------------------
alias vmip="ip -4 addr show eth0"
alias reload='source ~/.bashrc'
alias editrc='vim ~/.bashrc && reload'

# --------------------------------------

export PYENV_ROOT="$HOME/.pyenv"
export PATH="$PYENV_ROOT/bin:$PATH"


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

function update_rc() {
    vim ~/.bashrc && reload && echo "Bashrc changed successfully. Nice !!."
}

# --------------------------------------
function show_rc(){
  cat ~/.bashrc 
}
# --------------------------------------
