import { unit } from "mathjs";

import Module, { type MainModule } from "./public/wpilib.js";

// @ts-ignore - Module is actually an async function which loads the wasm and returns the MainModule type object
const module = (await Module()) as MainModule;

// @ts-ignore adding this function to be called by C++
globalThis.toUnitMathJS = function (value: number, unitStr: string) {
  return unit(value, unitStr);
};

const { Translation2d, Rotation2d, Pose2d } = module;

export { Translation2d, Rotation2d, Pose2d };
