// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder;

internal static class BitMask
{
    public static uint Get(uint bits, int shift, int mask) => (uint)((bits >> shift) & mask);

    public static uint Set(uint bits, uint value, int shift, int mask) =>
        (uint)((bits & (~mask << shift)) | ((value & mask) << shift));
}
