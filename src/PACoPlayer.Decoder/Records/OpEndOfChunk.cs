// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.Records;

public record OpEndOfChunk : OpHeader
{
    public OpEndOfChunk(OpHeader header) : base(header)
    {
    }

    public override string ToString() =>
        base.ToString();
}
