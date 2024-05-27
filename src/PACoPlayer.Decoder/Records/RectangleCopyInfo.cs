// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record RectangleCopyInfo
{
    public Point SourcePoint { get; init; }
    public Rectangle SourceRect { get; init; }
    public Point DestinationPoint { get; init; }
}
