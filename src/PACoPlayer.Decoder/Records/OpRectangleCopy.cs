// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpRectangleCopy : OpHeader
{
    private readonly byte _bits1;

    public OpRectangleCopy(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        RectangleCount = reader.ReadByte();
        _bits1 = reader.ReadByte();

        CopyRectangles = new List<RectangleCopyInfo>(RectangleCount);

        for (int i = 0; i < RectangleCount; i++)
        {
            CopyRectangles[i] = new()
            {
                SourcePoint = new()
                {
                    Left = reader.ReadByte(),
                    Top = reader.ReadByte(),
                },
                SourceRect = new()
                {
                    Width = reader.ReadByte(),
                    Height = reader.ReadByte(),
                },
                DestinationPoint = new()
                {
                    Left = reader.ReadByte(),
                    Top = reader.ReadByte(),
                },
            };
        }
    }

    public int RectangleCount { get; init; }
    public bool OnlyOnce => BitMask.Get(_bits1, 7, 1) == 1;
    public IList<RectangleCopyInfo> CopyRectangles { get; init; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"Rectangle copy count: {RectangleCount}");

        if (OnlyOnce) { _ = sb.AppendLine("- Only once"); }

        return sb.ToString();
    }
}
