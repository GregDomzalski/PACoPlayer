// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.DataTypes;

public enum OpCodeKind
{
    None,
    Transition,
    Palette,
    Delay,
    Sound,
    Cycle,
    Fill,
    Input,
    Bitmap,
    RectangleCopy,
    Break,
    EndOfChunk,
}
