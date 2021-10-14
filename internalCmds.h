#ifndef INTERNALCMDS_H
#define INTERNALCMDS_H

void parseInternalCommands(InternalFlags *flags,StringArray *cmds);
void executeInternalCommands(InternalFlags *flags,StringArray *cmds);
#endif