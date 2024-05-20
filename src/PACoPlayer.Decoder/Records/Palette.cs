// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Globalization;
using System.Text;

namespace PACoPlayer.Decoder.Records;

public record Palette
{
    public ICollection<Color> Colors { get; init; } = [];

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine("Color palette:");

        int i = 0;
        foreach (Color c in Colors)
        {
            _ = sb.AppendLine(CultureInfo.InvariantCulture, $"{i++:D3}: {c.ToString()}");
        }

        return sb.ToString();
    }
}
