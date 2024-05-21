// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpBreak : OpHeader
{
    public OpBreak(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        UserData = reader.ReadInt32BigEndian();
    }

    public int UserData { get; init; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- UserData: {UserData:X8}");

        return sb.ToString();
    }
}
