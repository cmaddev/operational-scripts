#!/bin/bash

SSH_ENV="$HOME/.ssh/agent-environment"

function start_agent {
    (umask 077; ssh-agent -s > "${SSH_ENV}")
    echo "Agente SSH iniciado"
    source "${SSH_ENV}"
    ssh-add /caminho/para/sua/chave_privada
}

if [ -f "${SSH_ENV}" ]; then
    source "${SSH_ENV}" > /dev/null
    ps -ef | grep ${SSH_AGENT_PID} | grep ssh-agent$ > /dev/null || {
        start_agent
    }
else
    start_agent
fi