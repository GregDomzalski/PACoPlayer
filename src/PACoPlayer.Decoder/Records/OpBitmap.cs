// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;
using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record OpBitmap : OpHeader
{
    private readonly ushort _bits;

    public OpBitmap(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        Origin = new()
        {
            Left = reader.ReadUInt16BigEndian(),
            Top = reader.ReadUInt16BigEndian(),
        };

        Size = new()
        {
            Width = reader.ReadUInt16BigEndian(),
            Height = reader.ReadUInt16BigEndian(),
        };

        _bits = reader.ReadUInt16BigEndian();
        BitmapData = reader.ReadBytes(header.Length - 14).ToArray();
    }

    public Point Origin { get; init; }
    public Rectangle Size { get; init; }
    public bool BlackAndWhite => BitMask.Get(_bits, 15, 1) == 1;
    public bool DiffsOnly => BitMask.Get(_bits, 14, 1) == 1;
    public bool LutEncoded => BitMask.Get(_bits, 13, 1) == 1;
    public CompressionKind Compression => (CompressionKind)BitMask.Get(_bits, 8, 0xF);
    public ReadOnlyMemory<byte> BitmapData { get; init; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Left: {Origin.Left}, Top: {Origin.Top}, Width: {Size.Width}px, Height: {Size.Height}px")
            .AppendLine($"- Compression type: {Compression}");

        if (BlackAndWhite) { _ = sb.AppendLine("- Black & white"); }

        if (DiffsOnly) { _ = sb.AppendLine("- Only differences from previous frame"); }

        if (LutEncoded) { _ = sb.AppendLine("- LUT encoded"); }

        return sb.ToString();
    }
}
