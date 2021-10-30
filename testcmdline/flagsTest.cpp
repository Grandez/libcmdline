#include "pch.h"

#include "_global.hpp"

TEST(Flags, flags_active_01) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("+v");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
TEST(Flags, flags_active_02) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("+verbose");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
TEST(Flags, flags_active_03) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("-v", "+v");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
TEST(Flags, flags_chain_01) {
	tool.reset();
	const char* fv = "verbose";
	const char* fc = "console";
	Parameters  parms = { ParmFlag(fv),  ParmFlag(fc) };
	tool.addArg("+vc");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag(fv));
	EXPECT_TRUE(cmdline.hasFlag(fc));
	CmdLine::freeInstance();
}
TEST(Flags, flags_chain_02) {
	tool.reset();
	const char* fv = "verbose";
	const char* fc = "console";
	Parameters  parms = { ParmFlag(fv),  ParmFlag(fc) };
	tool.addArg("+vc", "-console");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag(fv));
	EXPECT_FALSE(cmdline.hasFlag(fc));
	CmdLine::freeInstance();
}
TEST(Flags, flags_inactive_01) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("-v" );
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_FALSE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
TEST(Flags, flags_inactive_02) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("-verbose");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_FALSE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
TEST(Flags, flags_inactive_03) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	tool.addArg("+v", "-verbose");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_FALSE(cmdline.hasFlag("verbose"));
	CmdLine::freeInstance();
}
