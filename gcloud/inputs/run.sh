#!/usr/bin/env bash
#
# Depends on these environment variables being defined before executing:
#   - $MELEE_AI_INPUT_PATH
#   - $MELEE_AI_OUTPUT_PATH
#   - $MELEE_AI_GIT_REF

set -x  # echo commands to stdout
set -u  # throw an error if unset variable referenced
set -e  # exit on error

mkdir $MELEE_AI_OUTPUT_PATH

pushd melee-ai/
git checkout master  # TODO figure out if and why this is needed.
git pull --all
git checkout $MELEE_AI_GIT_REF

#TODO add --ai_input_dir=$MELEE_AI_INPUT_PATH --ai_output_dir=$MELEE_AI_OUTPUT_PATH
(time python3 tabular_trainer.py --dolphin --iso ~/SSBM.iso --cpu 9 --stage final_destination) &> $MELEE_AI_OUTPUT_PATH/_worker_output.txt
popd

date > $MELEE_AI_OUTPUT_PATH/_done.txt
