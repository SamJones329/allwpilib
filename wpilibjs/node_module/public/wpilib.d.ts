export interface CoordinateAxis {
  delete(): void;
}

export interface CoordinateSystem {
  delete(): void;
}

export interface Pose2d {
  relativeTo(_0: Pose2d): Pose2d;
  rotation(): Rotation2d;
  rotateBy(_0: Rotation2d): Pose2d;
  plus(_0: Transform2d): Pose2d;
  minus(_0: Pose2d): Transform2d;
  transformBy(_0: Transform2d): Pose2d;
  translation(): Translation2d;
  exp(_0: Twist2d): Pose2d;
  log(_0: Pose2d): Twist2d;
  equals(_0: Pose2d): boolean;
  times(_0: number): Pose2d;
  divideBy(_0: number): Pose2d;
  x(): any;
  y(): any;
  nearest(_0: any): Pose2d;
  delete(): void;
}

export interface vector<Pose2d> {
  push_back(_0: Pose2d): void;
  resize(_0: number, _1: Pose2d): void;
  size(): number;
  set(_0: number, _1: Pose2d): boolean;
  get(_0: number): any;
  delete(): void;
}

export interface Pose3d {
  delete(): void;
}

export interface Quaternion {
  delete(): void;
}

export interface Rotation2d {
  plus(_0: Rotation2d): Rotation2d;
  minus(_0: Rotation2d): Rotation2d;
  negated(): Rotation2d;
  rotateBy(_0: Rotation2d): Rotation2d;
  equals(_0: Rotation2d): boolean;
  times(_0: number): Rotation2d;
  divideBy(_0: number): Rotation2d;
  cos(): number;
  sin(): number;
  tan(): number;
  value(): any;
  delete(): void;
}

export interface Rotation3d {
  delete(): void;
}

export interface Transform2d {
  rotation(): Rotation2d;
  inverse(): Transform2d;
  plus(_0: Transform2d): Transform2d;
  translation(): Translation2d;
  equals(_0: Transform2d): boolean;
  times(_0: number): Transform2d;
  divideBy(_0: number): Transform2d;
  x(): any;
  y(): any;
  delete(): void;
}

export interface Transform3d {
  delete(): void;
}

export interface Translation2d {
  angle(): Rotation2d;
  rotateBy(_0: Rotation2d): Translation2d;
  plus(_0: Translation2d): Translation2d;
  minus(_0: Translation2d): Translation2d;
  negated(): Translation2d;
  equals(_0: Translation2d): boolean;
  times(_0: number): Translation2d;
  divideBy(_0: number): Translation2d;
  distance(_0: Translation2d): any;
  x(): any;
  y(): any;
  norm(): any;
  nearest(_0: any): Translation2d;
  delete(): void;
}

export interface Translation3d {
  delete(): void;
}

export interface Twist2d {
  equals(_0: Twist2d): boolean;
  times(_0: number): Twist2d;
  delete(): void;
}

export interface Twist3d {
  delete(): void;
}

export interface MainModule {
  CoordinateAxis: {new(_0: CoordinateAxis): CoordinateAxis; N(): CoordinateAxis; S(): CoordinateAxis; E(): CoordinateAxis; W(): CoordinateAxis; U(): CoordinateAxis; D(): CoordinateAxis};
  CoordinateSystem: {new(_0: CoordinateSystem): CoordinateSystem; NWU(): CoordinateSystem; EDN(): CoordinateSystem; NED(): CoordinateSystem};
  Pose2d: {new(): Pose2d};
  vector<Pose2d>: {new(): vector<Pose2d>};
  Pose3d: {new(): Pose3d};
  Quaternion: {new(): Quaternion};
  Rotation2d: {new(): Rotation2d};
  Rotation3d: {new(): Rotation3d};
  Transform2d: {new(): Transform2d};
  Transform3d: {new(): Transform3d};
  Translation2d: {new(): Translation2d};
  Translation3d: {new(): Translation3d};
  Twist2d: {new(): Twist2d};
  Twist3d: {new(): Twist3d};
}
