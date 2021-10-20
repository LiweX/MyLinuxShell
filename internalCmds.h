#ifndef INTERNALCMDS_H
#define INTERNALCMDS_H

void parseCommands(InternalFlags *flags,StringArray *cmds);
void executeInternalCommands(InternalFlags *flags,StringArray *cmds);
#endif