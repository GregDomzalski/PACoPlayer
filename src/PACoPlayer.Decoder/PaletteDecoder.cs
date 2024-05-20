// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using BinForge;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.Decoder;

public static class PaletteDecoder
{
    public static Palette DecodePalette(ref SpanReader reader, int colorCount)
    {
        Color[] colors = new Color[colorCount];

        for (int i = 0; i < colorCount; i++)
        {
            colors[i] = new()
            {
                Red = reader.ReadByte(),
                Green = reader.ReadByte(),
                Blue = reader.ReadByte(),
            };
        }

        return new() { Colors = colors };
    }
}
