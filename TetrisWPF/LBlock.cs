﻿using TetrisWPF;
public class LBlock : Block
{
    private readonly Position[][] tiles = new Position[][]
    {
            new Position[] { new Position(0, 1), new Position(1, 1), new Position(2, 1), new Position(2, 2) },
            new Position[] { new Position(0, 0), new Position(0, 1), new Position(0, 2), new Position(1, 0) },
            new Position[] { new Position(0, 0), new Position(0, 1), new Position(1, 1), new Position(2, 1) },
            new Position[] { new Position(0, 2), new Position(1, 0), new Position(1, 1), new Position(1, 2) }
    };

    public override int Id => 3;
    protected override Position StartOffset => new Position(-1, 3);
    protected override Position[][] Tiles => tiles;
}
