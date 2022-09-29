destinations = (input()).split()
graph = {}

def scan(transport, start = "home", end = "Waterloo GO"):
  queue = [(start, 0)]
  visited = set()
  
  while queue:
    vertex = queue.pop(0)
    count = vertex[1]
    vertex = vertex[0]
    if vertex in transport:
      for neighbour in transport[vertex]:
        if neighbour not in visited:
          queue.append((neighbour, count + 1,))
          visited.add(neighbour)
          if neighbour == end:
            return (count + 1)
  return ("RIP ACE")
  
for i in range(int(destinations[0])):
  begin = input()
  
for i in range(int(destinations[1])):
  transfer = input().split("-")
  if transfer[0] not in graph:
    graph[transfer[0]] = (transfer[1],)
  else:
    graph[transfer[0]] += (transfer[1],)
  if transfer[1] not in graph:
    graph[transfer[1]] = (transfer[0],)
  else:
    graph[transfer[1]] += (transfer[0],)
    
print (scan(graph))