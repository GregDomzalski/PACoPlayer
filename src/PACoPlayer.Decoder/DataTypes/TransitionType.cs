// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.DataTypes;

/// <summary>
/// Old-style transition types. These now map directly to custom types when packed. They are here for backwards
/// compatibility and preservation purposes.
/// </summary>
public enum TransitionType
{
    /// <summary>
    /// Unpack directly to the screen (transition no-op)
    /// </summary>
    Direct,

    /// <summary>
    /// Unpack offscreen, but then blit as fast as possible .
    /// </summary>
    Indirect,

    /// <summary>
    /// Unpack offscreen, but then blit as fast as possible interlaced. (Hides flumping [sic])
    /// </summary>
    IndirectInterlaced,

    /// <summary>
    /// Transfer bits from bottom to top.
    /// </summary>
    WipeUp,

    WipeLeft,
    WipeDown,
    WipeRight,
    PushUp,
    PushLeft,
    PushDown,
    PushRight,
    RevealUp,
    RevealLeft,
    RevealDown,
    RevealRight,
    CoverUp,
    CoverDown,
    CoverRight,
    RandomBars,
    RandomColumns,
    RandomSquares,
    DissolveFast,
    DissolveSlow,
    IrisOpen,
    IrisClose,
    WipeRectOpen,
    WipeRectClose,
    ProgressiveRefine,
    WipeHorizontalOpen,
    WipeHorizontalClose,
    WipeVerticalOpen,
    WipeVerticalClose,
    RandomTransition,
    Checkerboard,
    VenetianBlinds,
    Stair4LeftLeadTop,
    Stair5LeftLeadTop,
    CustomTransition = 255,
}
