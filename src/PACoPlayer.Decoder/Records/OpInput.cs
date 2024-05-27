// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpInput : OpHeader
{
    private ushort _bits1;

    public OpInput(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        _bits1 = reader.ReadUInt16BigEndian();
        reader.Skip(2);
    }

    public bool KeyPress => BitMask.Get(_bits1, 15, 1) == 1;
    public bool MouseClick => BitMask.Get(_bits1, 14, 1) == 1;
    public bool EatEvent => BitMask.Get(_bits1, 13, 1) == 1;
    public bool ShowCursor => BitMask.Get(_bits1, 12, 1) == 1;

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString());

        if (KeyPress) { _ = sb.AppendLine("- KeyPress"); }

        if (MouseClick) { _ = sb.AppendLine("- MouseClick"); }

        if (EatEvent) { _ = sb.AppendLine("- EatEvent"); }

        if (ShowCursor) { _ = sb.AppendLine("- ShowCursor"); }

        return sb.ToString();
    }
}
