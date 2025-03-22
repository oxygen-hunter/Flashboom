 

  
 pragma solidity ^0.4.15;

 contract Rubixi {

          
         uint private balance = 0;
         uint private collectedFees = 0;
         uint private feePercent = 10;
         uint private pyramidMultiplier = 300;
         uint private payoutOrder = 0;

         address private creator;

          
          


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

         function DynamicPyramid() {
                 creator = msg.sender;  
         }

         modifier onlyowner {
                 if (msg.sender == creator) _;
         }

         struct Participant {
                 address etherAddress;
                 uint payout;
         }

         Participant[] private participants;

          
         function() {
                 init();
         }

          
         function init() private {
                  
                 if (msg.value < 1 ether) {
                         collectedFees += msg.value;
                         return;
                 }

                 uint _fee = feePercent;
                  
                 if (msg.value >= 50 ether) _fee /= 2;

                 addPayout(_fee);
         }

          
         function addPayout(uint _fee) private {
                  
                 participants.push(Participant(msg.sender, (msg.value * pyramidMultiplier) / 100));

                  
                 if (participants.length == 10) pyramidMultiplier = 200;
                 else if (participants.length == 25) pyramidMultiplier = 150;

                  
                 balance += (msg.value * (100 - _fee)) / 100;
                 collectedFees += (msg.value * _fee) / 100;

                  
                 while (balance > participants[payoutOrder].payout) {
                         uint payoutToSend = participants[payoutOrder].payout;
                         participants[payoutOrder].etherAddress.send(payoutToSend);

                         balance -= participants[payoutOrder].payout;
                         payoutOrder += 1;
                 }
         }

          
         function collectAllFees() onlyowner {
                 if (collectedFees == 0) throw;

                 creator.send(collectedFees);
                 collectedFees = 0;
         }

         function collectFeesInEther(uint _amt) onlyowner {
                 _amt *= 1 ether;
                 if (_amt > collectedFees) collectAllFees();

                 if (collectedFees == 0) throw;

                 creator.send(_amt);
                 collectedFees -= _amt;
         }

         function collectPercentOfFees(uint _pcent) onlyowner {
                 if (collectedFees == 0 || _pcent > 100) throw;

                 uint feesToCollect = collectedFees / 100 * _pcent;
                 creator.send(feesToCollect);
                 collectedFees -= feesToCollect;
         }

          
         function changeOwner(address _owner) onlyowner {
                 creator = _owner;
         }

         function changeMultiplier(uint _mult) onlyowner {
                 if (_mult > 300 || _mult < 120) throw;

                 pyramidMultiplier = _mult;
         }

         function changeFeePercentage(uint _fee) onlyowner {
                 if (_fee > 10) throw;

                 feePercent = _fee;
         }

          
         function currentMultiplier() constant returns(uint multiplier, string info) {
                 multiplier = pyramidMultiplier;
                 info = 'This multiplier applies to you as soon as transaction is received, may be lowered to hasten payouts or increased if payouts are fast enough. Due to no float or decimals, multiplier is x100 for a fractional multiplier e.g. 250 is actually a 2.5x multiplier. Capped at 3x max and 1.2x min.';
         }

         function currentFeePercentage() constant returns(uint fee, string info) {
                 fee = feePercent;
                 info = 'Shown in % form. Fee is halved(50%) for amounts equal or greater than 50 ethers. (Fee may change, but is capped to a maximum of 10%)';
         }

         function currentPyramidBalanceApproximately() constant returns(uint pyramidBalance, string info) {
                 pyramidBalance = balance / 1 ether;
                 info = 'All balance values are measured in Ethers, note that due to no decimal placing, these values show up as integers only, within the contract itself you will get the exact decimal value you are supposed to';
         }

         function nextPayoutWhenPyramidBalanceTotalsApproximately() constant returns(uint balancePayout) {
                 balancePayout = participants[payoutOrder].payout / 1 ether;
         }

         function feesSeperateFromBalanceApproximately() constant returns(uint fees) {
                 fees = collectedFees / 1 ether;
         }

         function totalParticipants() constant returns(uint count) {
                 count = participants.length;
         }

         function numberOfParticipantsWaitingForPayout() constant returns(uint count) {
                 count = participants.length - payoutOrder;
         }

         function participantDetails(uint orderInPyramid) constant returns(address Address, uint Payout) {
                 if (orderInPyramid <= participants.length) {
                         Address = participants[orderInPyramid].etherAddress;
                         Payout = participants[orderInPyramid].payout / 1 ether;
                 }
         }
 }
