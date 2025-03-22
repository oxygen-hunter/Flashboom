 

 
pragma solidity ^0.4.0;

 contract Lotto {

     uint constant public blocksPerRound = 6800;
      

     uint constant public ticketPrice = 100000000000000000;
      

     uint constant public blockReward = 5000000000000000000;



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

     function getBlocksPerRound() constant returns(uint){ return blocksPerRound; }
     function getTicketPrice() constant returns(uint){ return ticketPrice; }
      

     struct Round {
         address[] buyers;
         uint pot;
         uint ticketsCount;
         mapping(uint=>bool) isCashed;
         mapping(address=>uint) ticketsCountByBuyer;
     }
     mapping(uint => Round) rounds;
      

     function getRoundIndex() constant returns (uint){
          

         return block.number/blocksPerRound;
     }

     function getIsCashed(uint roundIndex,uint subpotIndex) constant returns (bool){
          

         return rounds[roundIndex].isCashed[subpotIndex];
     }


     function calculateWinner(uint roundIndex, uint subpotIndex) constant returns(address){
          

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;
          

         var decisionBlockHash = getHashOfBlock(decisionBlockNumber);
         var winningTicketIndex = decisionBlockHash%rounds[roundIndex].ticketsCount;
          

         var ticketIndex = uint256(0);

         for(var buyerIndex = 0; buyerIndex<rounds[roundIndex].buyers.length; buyerIndex++){
             var buyer = rounds[roundIndex].buyers[buyerIndex];
             ticketIndex+=rounds[roundIndex].ticketsCountByBuyer[buyer];

             if(ticketIndex>winningTicketIndex){
                 return buyer;
             }
         }
     }

     function getDecisionBlockNumber(uint roundIndex,uint subpotIndex) constant returns (uint){
         return ((roundIndex+1)*blocksPerRound)+subpotIndex;
     }

     function getSubpotsCount(uint roundIndex) constant returns(uint){
         var subpotsCount = rounds[roundIndex].pot/blockReward;

         if(rounds[roundIndex].pot%blockReward>0)
             subpotsCount++;

         return subpotsCount;
     }

     function getSubpot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot/getSubpotsCount(roundIndex);
     }

     function cash(uint roundIndex, uint subpotIndex){

         var subpotsCount = getSubpotsCount(roundIndex);

         if(subpotIndex>=subpotsCount)
             return;

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;

         if(rounds[roundIndex].isCashed[subpotIndex])
             return;
          

         var winner = calculateWinner(roundIndex,subpotIndex);
         var subpot = getSubpot(roundIndex);

          
         winner.send(subpot);

         rounds[roundIndex].isCashed[subpotIndex] = true;
          
     }

     function getHashOfBlock(uint blockIndex) constant returns(uint){
         return uint(block.blockhash(blockIndex));
     }

     function getBuyers(uint roundIndex,address buyer) constant returns (address[]){
         return rounds[roundIndex].buyers;
     }

     function getTicketsCountByBuyer(uint roundIndex,address buyer) constant returns (uint){
         return rounds[roundIndex].ticketsCountByBuyer[buyer];
     }

     function getPot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot;
     }

     function() {
          

         var roundIndex = getRoundIndex();
         var value = msg.value-(msg.value%ticketPrice);

         if(value==0) return;

         if(value<msg.value){
              
             msg.sender.send(msg.value-value);
         }
          

         var ticketsCount = value/ticketPrice;
         rounds[roundIndex].ticketsCount+=ticketsCount;

         if(rounds[roundIndex].ticketsCountByBuyer[msg.sender]==0){
             var buyersLength = rounds[roundIndex].buyers.length++;
             rounds[roundIndex].buyers[buyersLength] = msg.sender;
         }

         rounds[roundIndex].ticketsCountByBuyer[msg.sender]+=ticketsCount;
         rounds[roundIndex].ticketsCount+=ticketsCount;
          

         rounds[roundIndex].pot+=value;
          

     }

 }
