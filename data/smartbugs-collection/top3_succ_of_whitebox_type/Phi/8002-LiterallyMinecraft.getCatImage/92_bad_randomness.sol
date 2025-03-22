 

 pragma solidity ^0.4.16;

contract Ethraffle_v4b {
    struct Contestant {
        address addr;
        uint raffleId;
    }

    event RaffleResult(
        uint raffleId,
        uint winningNumber,
        address winningAddress,
        address seed1,
        address seed2,
        uint seed3,
        bytes32 randHash
    );

    event TicketPurchase(
        uint raffleId,
        address contestant,
        uint number
    );

    event TicketRefund(
        uint raffleId,
        address contestant,
        uint number
    );

     
    uint public constant prize = 2.5 ether;
    uint public constant fee = 0.03 ether;
    uint public constant totalTickets = 50;
    uint public constant pricePerTicket = (prize + fee) / totalTickets;  
    address feeAddress;

     
    bool public paused = false;
    uint public raffleId = 1;
     
    uint public blockNumber = block.number;
    uint nextTicket = 0;
    mapping (uint => Contestant) contestants;
    uint[] gaps;

     


contract LiterallyMinecraft {

  uint constant global_width = 32;
  uint constant global_height = 32;
  uint constant chunk_size = 32;

  struct Chunk {
    bytes32[chunk_size] colors;
    address owner;
    uint value;
  }

  Chunk[global_width * global_height] public screen;

  uint[global_width * global_height] public lastUpdateByChunk;

  function getIndex(uint8 x, uint8 y) public pure returns(uint) {
    return y*global_width+x;
  }

  function getChunk(uint8 x, uint8 y) external view
    withinBounds(x,y)
    returns(bytes32[chunk_size], address, uint, uint)
  {
    uint index = getIndex(x,y);
    
    if (lastUpdateByChunk[index] == 0)     // initial default image is gaint cat
      return (getCatImage(x,y), 0x0, 0, 0);
    
    Chunk storage p = screen[index];
    return (p.colors, p.owner, p.value, lastUpdateByChunk[index]);
  }

  modifier withinBounds(uint8 x, uint8 y) {
    require(x >= 0 && x < global_width, "x out of range");
    require(y >= 0 && y < global_height, "y out of range");
    _;
  }

  function getCatImage(uint8 x, uint8 y) internal pure
    returns(bytes32[chunk_size])
  {
    bytes32[chunk_size] memory cat;
    cat[0] =  hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[1] =  hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[2] =  hex"0000e3e300e0e0e0001c1c1c0000000000000000000000000000000000000000";
    cat[3] =  hex"0000e30000e000e000001c000000000000fc000000fc0000000000f0f0f00000";
    cat[4] =  hex"0000e30000e0e0e000001c000000000000fcfc00fcfc0000000000f000000000";
    cat[5] =  hex"0000e3e300e000e000001c000000000000fcfcfcfcfc0000000000f000f00000";
    cat[6] =  hex"00000000000000000000000000000000fcfcfcfcfcfcfc00000000f0f0f00000";
    cat[7] =  hex"000000000000000000000000000000fcfcfcfcfcfcfcfcfc0000000000000000";
    cat[8] =  hex"00000000000000000000000000001ffcfc0000fcfc0000fc000000fcfcfc0000";
    cat[9] =  hex"00000000000000000000000000001ffcfcfcfcfcfcfcfcfc000000fc00fc0000";
    cat[10] = hex"00000000000000ff000000001f1f1ffcfcfcfc0000fcfcfc000000fcfcfc0000";
    cat[11] = hex"0000000000ffff00000000001f1f1f1ffcfc00fcfc00fc00000000fc00fc0000";
    cat[12] = hex"00000000ff0000000000001f1ffcfc1f1ffcfcfcfcfc1f1f0000000000000000";
    cat[13] = hex"000000ff00000000ff00000000fcfc1f1f1f1f1f1f1f1f1f00001f0000001f00";
    cat[14] = hex"0000ff000000ffff00000000fcfc1f1f1f1f1f1f1f1f1f1f00001f1f001f1f00";
    cat[15] = hex"0000ffff00ff00000000fcfcfc001f1f1ffc1f1f1f1f1f0000001f001f001f00";
    cat[16] = hex"000000ffff000000ffff00000000001ffcfc1f1f1f1f1f0000001f0000001f00";
    cat[17] = hex"00000000ffff00ff00000000ff000000fc1f1f1f1f1f1f0000001f0000001f00";
    cat[18] = hex"0000000000ffff000000ffff0000fcfc001f1f1f1f1f00000000000000000000";
    cat[19] = hex"000000000000ffff00ff00000000ff0000001f1f1f000000000000ffffff0000";
    cat[20] = hex"00000000000000ffff000000ffff00000000001f1f000000000000ff00000000";
    cat[21] = hex"0000000000000000ffff00ff00000000ff00000000000000000000ffff000000";
    cat[22] = hex"000000000000000000ffff000000ffff0000000000000000000000ff00000000";
    cat[23] = hex"00000000000000000000ffff00ff00000000ff0000000000000000ffffff0000";
    cat[24] = hex"0000000000000000000000ffff000000ffff00000000ff000000000000000000";
    cat[25] = hex"000000000000000000000000ffff00ff00000000ff0000ff0000000000000000";
    cat[26] = hex"00000000000000000000000000ffff000000ffff0000ff000000000000000000";
    cat[27] = hex"0000000000000000000000000000ffff00ff000000ff00000000000000000000";
    cat[28] = hex"000000000000000000000000000000ffff0000ffff0000000000000000000000";
    cat[29] = hex"00000000000000000000000000000000ffffff00000000000000000000000000";
    cat[30] = hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[31] = hex"0000000000000000000000000000000000000000000000000000000000000000";

    bytes32 pixel_row = cat[y][x];
      
    pixel_row |= (pixel_row >> 1*8);
    pixel_row |= (pixel_row >> 2*8);
    pixel_row |= (pixel_row >> 4*8);
    pixel_row |= (pixel_row >> 8*8);
    pixel_row |= (pixel_row >> 16*8);

    for (y = 0; y < 32; ++y)
      cat[y] = pixel_row;

    return cat;
  }

    function Ethraffle_v4b() public {
        feeAddress = msg.sender;
    }

     
    function () payable public {
        buyTickets();
    }

    function buyTickets() payable public {
        if (paused) {
            msg.sender.transfer(msg.value);
            return;
        }

        uint moneySent = msg.value;

        while (moneySent >= pricePerTicket && nextTicket < totalTickets) {
            uint currTicket = 0;
            if (gaps.length > 0) {
                currTicket = gaps[gaps.length-1];
                gaps.length--;
            } else {
                currTicket = nextTicket++;
            }

            contestants[currTicket] = Contestant(msg.sender, raffleId);
            TicketPurchase(raffleId, msg.sender, currTicket);
            moneySent -= pricePerTicket;
        }

         
        if (nextTicket == totalTickets) {
            chooseWinner();
        }

         
        if (moneySent > 0) {
            msg.sender.transfer(moneySent);
        }
    }

    function chooseWinner() private {
         
        address seed1 = contestants[uint(block.coinbase) % totalTickets].addr;
         
        address seed2 = contestants[uint(msg.sender) % totalTickets].addr;
         
        uint seed3 = block.difficulty;
        bytes32 randHash = keccak256(seed1, seed2, seed3);

        uint winningNumber = uint(randHash) % totalTickets;
        address winningAddress = contestants[winningNumber].addr;
        RaffleResult(raffleId, winningNumber, winningAddress, seed1, seed2, seed3, randHash);

         
        raffleId++;
        nextTicket = 0;
         
        blockNumber = block.number;

         
         
         

         
        winningAddress.transfer(prize);
        feeAddress.transfer(fee);
    }

     
    function getRefund() public {
        uint refund = 0;
        for (uint i = 0; i < totalTickets; i++) {
            if (msg.sender == contestants[i].addr && raffleId == contestants[i].raffleId) {
                refund += pricePerTicket;
                contestants[i] = Contestant(address(0), 0);
                gaps.push(i);
                TicketRefund(raffleId, msg.sender, i);
            }
        }

        if (refund > 0) {
            msg.sender.transfer(refund);
        }
    }

     
    function endRaffle() public {
        if (msg.sender == feeAddress) {
            paused = true;

            for (uint i = 0; i < totalTickets; i++) {
                if (raffleId == contestants[i].raffleId) {
                    TicketRefund(raffleId, contestants[i].addr, i);
                    contestants[i].addr.transfer(pricePerTicket);
                }
            }

            RaffleResult(raffleId, totalTickets, address(0), address(0), address(0), 0, 0);
            raffleId++;
            nextTicket = 0;
             
            blockNumber = block.number;
            gaps.length = 0;
        }
    }

    function togglePause() public {
        if (msg.sender == feeAddress) {
            paused = !paused;
        }
    }

    function kill() public {
        if (msg.sender == feeAddress) {
            selfdestruct(feeAddress);
        }
    }
}
