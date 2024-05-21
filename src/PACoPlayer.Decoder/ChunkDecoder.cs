// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using BinForge;
using PACoPlayer.Decoder.DataTypes;
using PACoPlayer.Decoder.Records;

namespace PACoPlayer.Decoder;

public static class ChunkDecoder
{
    public static OpHeader[] DecodeOpcodes(ReadOnlySpan<byte> chunk)
    {
        SpanReader reader = new(chunk);

        List<OpHeader> opCodes = [];

        while (reader.Position < reader.Span.Length) { opCodes.Add(ReadNextOpcode(ref reader)); }

        return opCodes.ToArray();
    }

    private static OpHeader ReadNextOpcode(ref SpanReader reader)
    {
        OpHeader header = new(reader.ReadUInt32BigEndian());

        return header.Kind switch
        {
            OpCodeKind.Transition => ReadTransitionOpcode(ref reader, header),
            OpCodeKind.Palette => ReadPaletteOpcode(ref reader, header),
            OpCodeKind.Delay => ReadDelayOpcode(ref reader, header),
            OpCodeKind.Sound => ReadSoundOpcode(ref reader, header),
            OpCodeKind.Bitmap => ReadBitmapOpcode(ref reader, header),
            OpCodeKind.Break => ReadBreakOpcode(ref reader, header),
            OpCodeKind.EndOfChunk => ReadEndOfChunk(ref reader, header),
            _ => header,
        };
    }

    private static OpTransition ReadTransitionOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, ref reader);

    private static OpPalette ReadPaletteOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, reader.ReadByte())
        {
            Time = TransitionTime.From(reader.ReadByte()),
            SolidColor = new()
            {
                Red = reader.ReadByte(),
                Green = reader.ReadByte(),
                Blue = reader.ReadByte(),
            },
            ColorTable = ReadColorTable(ref reader, reader.ReadByte()),
        };

    private static OpDelay ReadDelayOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, ref reader);

    private static OpSound ReadSoundOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, ref reader);

    private static Color[] ReadColorTable(ref SpanReader reader, byte numColors)
    {
        reader.Skip(2); // Filler bytes

        Color[] colors = new Color[numColors];

        for (int i = 0; i < numColors; i++)
        {
            colors[i] = new()
            {
                Red = reader.ReadByte(),
                Green = reader.ReadByte(),
                Blue = reader.ReadByte(),
            };
        }

        return colors;
    }

    private static OpBitmap ReadBitmapOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, ref reader);

    private static OpBreak ReadBreakOpcode(ref SpanReader reader, OpHeader header) =>
        new(header, ref reader);

    private static OpEndOfChunk ReadEndOfChunk(ref SpanReader _, OpHeader header) =>
        new(header);
}
